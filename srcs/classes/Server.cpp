#include "ft_irc.hpp"

// ---------------------------- //
// STATIC VARIABLES DECLARATION
// ---------------------------- //
int Server::_port;
std::string Server::_passwd;
sockAddrIn Server::_serverAddr;
int Server::_serverSocketDescriptor;
std::vector<pollfd> Server::_connections;
std::vector<Client> Server::_clients;

Server::Server() {}

Server::~Server() {}

// ---------------------------- //
// GETTERS AND SETTERS
// ---------------------------- //
void	Server::setPort(char *input)
{
	int port = std::atoi(input);

	if (port <= 0 || port > MAX_PORT_NUMBER)
		throw std::logic_error("Invalid port number");
	_port = port;
}

std::string Server::getPasswd()
{
	return (Server::_passwd);
}

static bool isPrintable(const std::string &s) {
	for (std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
		if (!std::isprint(static_cast<unsigned char>(*it))) {
			return false;
		}
	}
	return true;
}

void Server::setPasswd(char *passwd)
{
	if (!isPrintable(passwd) || !passwd[0])
		throw std::logic_error("Invalid password provided");
	Server::_passwd = std::string(passwd);
}

// ---------------------------- //
// PRIVATE MEMBER FUNCTIONS
// ---------------------------- //
void Server::bindSocketToAddress() {
	if (bind(Server::_serverSocketDescriptor, (sockAddr *) &_serverAddr, sizeof(_serverAddr)) < 0)
		throw std::runtime_error("Failed to bind server file descriptor to socket");
};

void Server::createSocket() {
	const int	ENABLE = 1;

	Server::_serverSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (Server::_serverSocketDescriptor < 0)
		throw std::runtime_error("Failed to create socket");
	if (setsockopt(Server::_serverSocketDescriptor, SOL_SOCKET, SO_REUSEADDR, &ENABLE, sizeof(int)) < 0)
		throw std::runtime_error("Failed to set socket options");
	// Configure socket descriptor to non-blocking 
	if (fcntl(Server::_serverSocketDescriptor, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Failed to set the non-blocking mode on socket file descriptor");
};

void Server::configureAddress() {
	std::memset(&_serverAddr, 0, sizeof(_serverAddr));
	_serverAddr.sin_family = AF_INET;
	_serverAddr.sin_addr.s_addr = INADDR_ANY;
	_serverAddr.sin_port = htons(_port);
};

void Server::listenForClients() {
	// Puts server to listen to port 8080 and sets a limit for the number of connections allowed to be held at 
	if(listen(Server::_serverSocketDescriptor, CLIENT_LIMIT) == -1)
		throw std::runtime_error("Failed to listen on socket");
};

void Server::sigHandler(int)
{
	close(Server::_serverSocketDescriptor);
	throw std::runtime_error("\nServer stopped by SIGINT");
}

// ---------------------------- //
// PUBLIC MEMBER FUNCTIONS
// ---------------------------- //
Server& Server::getInstance() {
/**
 * Singleton design pattern.
 * 
 * This function provides access to the single instance of Server.
 * Ensures that the instance is created only once.
*/
	static Server instance;

	return instance;
};

void Server::setUpTCP() {
	LOG("Setting up server...")
	createSocket();
	configureAddress();
	bindSocketToAddress();
	listenForClients();
	LOG("Server is all set.")
};

void	Server::pollForNewConnections(void) {
	// Poll goes through all the fds in the vector and sees if there is any queeued event.
	int activity = poll(_connections.data(), _connections.size(), TIMEOUT_MS);
	if (activity < 0)
		throw std::runtime_error("Poll error");

	// checks for new _connections to the server
	if ((_connections[0].revents & POLLIN) == POLLIN)
	{
		// ---------------- ACT 3 - inject connections (pollfds) into Clients
		Client newClient(Server::_serverSocketDescriptor);
		_connections.push_back((pollfd) { .fd = newClient.getFd(), .events = POLLIN});
		_clients.push_back(newClient);
	}
}

void	Server::processClientActivity(void) {
}

void	Server::start()
{
	// std::vector<pollfd> connections;	// morre e vai pra dentro do Client como uma variável estática
	// std::vector<Client> clients;
	std::vector<Channel> channels;

	// Overrides the behaviour of SIGINT (ctrl+C)
	signal(SIGINT, &Server::sigHandler);

	// First instance in vector corresponds to server's socket descriptor
	// Any new connections to server will come through the server's connection in the first place.
	_connections.push_back((pollfd) {.fd = Server::_serverSocketDescriptor, .events = POLLIN});

	LOG("Server running...")
	while (true)
	{
		// check for new connections
		pollForNewConnections();

		// process clients activities
		// processClientActivity();
		for (std::size_t i = 1; i < _connections.size(); i++)
		{
			if ((_connections[i].revents & POLLIN) == POLLIN)
			{
				Client &client = _clients[i - 1];

				client.incrementCurrCommand(Client::receiveData(client));
				if (client.getIsCommandComplete())
				{
					std::vector<std::string> lines = Utils::split(client.getCurrCommand(), "\r\n");
					for (std::vector<std::string>::iterator line = lines.begin(); line != lines.end(); line++)
					{
						if ((*line).empty())
							continue ;
						RawMessage msg = RawMessage::parseMsg(*line);
						std::pair<std::string, std::vector<Client> > response = RawMessage::processMessage(msg, client, _clients, channels);
						client.sendMessage(response);
						client.setIsCommandComplete(false);
						client.setCurrCommand("");
					}
				}
				if (client.getShouldEraseClient())
				{
					close(client.getFd());
					_clients.erase(_clients.begin() + (long)i - 1);
					_connections.erase(_connections.begin() + (long)i);
					for (size_t c = 0; c < channels.size(); c++)
						channels[c].disconnectClient(client);
					Client::decrementIdCounter();
				}
			}
		}
	}
}
