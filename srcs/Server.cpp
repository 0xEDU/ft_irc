#include "ft_irc.hpp"

std::string Server::_passwd;
int Server::_serverFd = 0;

Server::Server() : _port(0) {}

Server::~Server() {}

void	Server::setPort(char *input)
{
	int port = std::atoi(input);
	
	if (port < 0 || port > 65535)
		throw std::logic_error("Invalid port number");
	this->_port = port;
}

void Server::setupTCP() const {
	const int	enable = 1;
	sockAddrIn	serverAddr;
	
	Server::_serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (Server::_serverFd < 0)
		throw std::runtime_error("Failed to create socket");
	if (setsockopt(Server::_serverFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		throw std::runtime_error("setsockopt failed");
	std::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(this->_port);
	if (bind(Server::_serverFd, (sockAddr *) &serverAddr, sizeof(serverAddr)) < 0)
		throw std::runtime_error("Failed to bind to socket"); 
	int flags = fcntl(Server::_serverFd, F_GETFL, 0);
	if (fcntl(Server::_serverFd, F_SETFL, flags | O_NONBLOCK) == -1)
    	throw std::runtime_error("Failed to set socketFd to non-blocking");
	listen(Server::_serverFd, CLIENT_LIMIT);
}

void Server::sigHandler(int)
{
	close(Server::_serverFd);
	throw std::runtime_error("\nServer stopped by SIGINT");
}

void	Server::mainLoop()
{
	std::vector<pollfd> fds;
	std::vector<Client> clients;
	std::vector<Channel> channels;

	signal(SIGINT, &Server::sigHandler);
	fds.push_back((pollfd) {.fd = Server::_serverFd, .events = POLLIN});
	
	while (true)
	{
		int activity = poll(fds.data(), fds.size(), TIMEOUT);
		if (activity < 0)
		{
			ERROR("Poll error")
			continue;
		}
		if (fds[0].revents & POLLIN)
		{
			Client newClient(Server::_serverFd);
			fds.push_back((pollfd) { .fd = newClient.getFd(), .events = POLLIN});
			clients.push_back(newClient);
		}
		for (std::size_t i = 1; i < fds.size(); i++)
        {
			if (fds[i].revents & POLLIN)
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
						Message msg = Message::parseMsg(*line);
						std::pair<std::string, std::vector<Client> > response = Message::processMessage(msg, client, clients, channels);
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
		std::cout << "clients: " << clients.size() << std::endl;
		sleep(1); // Will be removed
	}
}

std::string Server::getPasswd()
{
	return (Server::_passwd);
}

void Server::setPasswd(char *passwd)
{
	Server::_passwd = std::string(passwd);
}