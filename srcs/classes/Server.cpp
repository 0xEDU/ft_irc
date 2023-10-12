#include "ft_irc.hpp"

// ---------------------------- //
// STATIC VARIABLES DECLARATION
// ---------------------------- //
std::string Server::_passwd;
int Server::_serverFd = 0;

Server::Server() : _port(0) {}

Server::~Server() {}

// ---------------------------- //
// GETTERS AND SETTERS
// ---------------------------- //
void	Server::setPort(char *input)
{
	int port = std::atoi(input);
	
	if (port <= 0 || port > MAX_PORT_NUMBER)
		throw std::logic_error("Invalid port number");
	this->_port = port;
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
	if (!isPrintable(passwd))
		throw std::logic_error("Invalid password provided");
	Server::_passwd = std::string(passwd);
}

// ---------------------------- //
// PRIVATE MEMBER FUNCTIONS
// ---------------------------- //
// void Server::bindSocket() {
// 	// TODO
// };

// void Server::createSocket() {
// 	// TODO
// };

// void Server::configureAddress() {
// 	// TODO
// };

// void Server::listenForClients() {
// 	// TODO
// };

void Server::sigHandler(int)
{
	close(Server::_serverFd);
	throw std::runtime_error("\nServer stopped by SIGINT");
}

// ---------------------------- //
// PUBLIC MEMBER FUNCTIONS
// ---------------------------- //
void Server::setUpTCP() const {
	// createSocket();
	// configureAddress();
	// bindSocket();
	// listenForClients();

	const int	ENABLE = 1;
	sockAddrIn	serverAddr;
	
	Server::_serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (Server::_serverFd < 0)
		throw std::runtime_error("Failed to create socket");
	if (setsockopt(Server::_serverFd, SOL_SOCKET, SO_REUSEADDR, &ENABLE, sizeof(int)) < 0)
		throw std::runtime_error("Failed to set socket options");
	std::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(this->_port);

	if (bind(Server::_serverFd, (sockAddr *) &serverAddr, sizeof(serverAddr)) < 0)
		throw std::runtime_error("Failed to bind server file descriptor to socket");

	// Configure file descriptor to non-blocking 
	int flags = fcntl(Server::_serverFd, F_GETFL, 0);
	if (fcntl(Server::_serverFd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw std::runtime_error("Failed to set the non-blocking mode on socket file descriptor");
	
	// Puts server to listen to port 8080 and sets a limit for the number of connections allowed to be held at 
	if(listen(Server::_serverFd, CLIENT_LIMIT) == -1)
		throw std::runtime_error("Failed to listen on socket");
}

void	Server::start()
{
	std::vector<pollfd> fds;
	std::vector<Client> clients;
	std::vector<Channel> channels;


	// Overrides the behaviour of SIGINt (ctrl+C)
	signal(SIGINT, &Server::sigHandler);

	// initialises this vector with the first POLLIN event i guess?
	//
	fds.push_back((pollfd) {.fd = Server::_serverFd, .events = POLLIN});
	LOG("Server running...")
	while (true)
	{
		// Poll goes through all the fds in the vector and sees if there is any queeued event.
		int activity = poll(fds.data(), fds.size(), TIMEOUT_MS);
		if (activity < 0)
			throw std::logic_error("Poll error");
		if (fds[0].revents & POLLIN)
		{
			Client newClient(Server::_serverFd);
			fds.push_back((pollfd) { .fd = newClient.getFd(), .events = POLLIN});
			clients.push_back(newClient);
		}

		for (std::size_t i = 1; i < fds.size(); i++)
		{
			if ((fds[i].revents & POLLIN) == POLLIN)
			{
				Client &client = clients[i - 1];

				client.incrementCurrCommand(Client::receiveData(client));
				if (client.getIsCommandComplete())
				{
					std::vector<std::string> lines = Utils::split(client.getCurrCommand(), "\r\n");
					for (std::vector<std::string>::iterator line = lines.begin(); line != lines.end(); line++)
					{
						if ((*line).empty())
							continue ;
						RawMessage msg = RawMessage::parseMsg(*line);
						std::pair<std::string, std::vector<Client> > response = RawMessage::processMessage(msg, client, clients, channels);
						client.sendMessage(response);
						client.setIsCommandComplete(false);
						client.setCurrCommand("");
					}
				}
				if (client.getShouldEraseClient())
				{
					close(client.getFd());
					clients.erase(clients.begin() + (long)i - 1);
					fds.erase(fds.begin() + (long)i);
					for (size_t c = 0; c < channels.size(); c++)
						channels[c].disconnectClient(client);
					Client::decrementIdCounter();
				}
			}
		}
	}
}
