#include "ft_irc.hpp"

// ---------------------------- //
// STATIC VARIABLES DECLARATION
// ---------------------------- //
int Server::_serverPort;
int Server::_serverSocketDescriptor;
pollfd *Server::_serverPollfd;
sockAddrIn Server::_serverAddr;
std::string Server::_serverPassword;

std::vector<pollfd> Server::_connectionsPollfds;
std::vector<Client> Server::_clients;
std::vector<Channel> Server::_channels;

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
	_serverPort = port;
}

std::string Server::getPasswd()
{
	return (Server::_serverPassword);
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
	Server::_serverPassword = std::string(passwd);
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
	_serverAddr.sin_port = htons(_serverPort);
};

void Server::listenForClients() {
	// Puts server to listen to a specified port and sets a limit for the number of connections allowed to be held at once
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

void	Server::pollActiveConnections(void) {
	// Goes through all the active connections and registers queued event.
	int activity = poll(_connectionsPollfds.data(), _connectionsPollfds.size(), TIMEOUT_MS);
	if (activity < 0)
		throw std::runtime_error("Polling error");
};

void	Server::acceptNewClients(void) {
	if ((_serverPollfd->revents & POLLIN) == POLLIN)
	{
		sockAddrIn newClientAddress;
		socklen_t addressLength = sizeof(newClientAddress);
		int newClientSocketDescriptor = accept(_serverSocketDescriptor, (sockAddr *) &newClientAddress, &addressLength);

		if (newClientSocketDescriptor < 0)
			throw std::runtime_error("Failed to accept new client");
		if (fcntl(newClientSocketDescriptor, F_SETFL, O_NONBLOCK) == -1)
			throw std::runtime_error("Failed to set client's socket descriptor to non-blocking mode");

		_connectionsPollfds.push_back((pollfd) { .fd = newClientSocketDescriptor, .events = POLLIN});

		Client newClient(newClientSocketDescriptor, _connectionsPollfds.back());
		_clients.push_back(newClient);
	}
};

void	Server::processClientsActivity(void) {
	for (std::vector<Client>::iterator client = _clients.begin(); client < _clients.end(); client++)
	{
		// if ()
		if (client->detectedActivity())
		{
			client->storeRawData(Client::receiveData(*client));
			client->pushToCommandQueue();

			// for (command in commandQueue) {
			// 	execute_command();
			// }

			// função que percorre os clients e faz clean up (kicka quem tem q kickar)

			// if (client->getIsCommandComplete())
			// {
			// 	std::vector<std::string> lines = Utils::split(client->getCurrCommand(), "\r\n");
				// for ( = lines.begin(); line != lines.end(); line++)
				std::queue<std::string> &commandsQueue = client->getCommandsQueue();
				while (!commandsQueue.empty()) {
					std::string line = commandsQueue.front();
					commandsQueue.pop();
					RawMessage msg = RawMessage::parseMsg(line);
					std::pair<std::string, std::vector<Client> > response = RawMessage::processMessage(msg, *client, _clients, _channels);
					client->sendMessage(response);
				}
				// {
				// 	if ((*line).empty())
				// 		continue ;
				// 	RawMessage msg = RawMessage::parseMsg(*line);
				// 	std::pair<std::string, std::vector<Client> > response = RawMessage::processMessage(msg, *client, _clients, _channels);
				// 	client->sendMessage(response);
				// 	client->setIsCommandComplete(false);
				// 	client->setCurrCommand("");
				// }
			// }
			if (client->getShouldEraseClient())
			{
				close(client->getFd());
				// usar find pra pegar o iterador do 
				_connectionsPollfds.erase(std::find(_connectionsPollfds.begin(), _connectionsPollfds.end(), client->getPollfdRef()));
				for (size_t c = 0; c < _channels.size(); c++)
					_channels[c].disconnectClient(*client);
				// usar o proprio cliente (iterador) da iteracao atual
				_clients.erase(client);
				Client::decrementIdCounter();
			}
		}
	}
}

void	Server::start()
{
	// Overrides the behaviour of SIGINT (ctrl+C)
	signal(SIGINT, &Server::sigHandler);

	// First instance in vector corresponds to server's socket descriptor
	// Any new connections to server will come through the server's connection in the first place.
	_connectionsPollfds.push_back((pollfd) {.fd = Server::_serverSocketDescriptor, .events = POLLIN});
	_serverPollfd = &Server::_connectionsPollfds[0];

	LOG("Server running...")
	while (true)
	{
		// check for new connections
		pollActiveConnections();

		// Process polled events for all active connections
		acceptNewClients();
		processClientsActivity();
	}
};
