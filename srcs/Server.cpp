#include "ft_irc.hpp"

int Server::_serverFd = 0;
std::string Server::_passwd = "";

Server::Server() {}

Server::~Server() {}

void	Server::setPort(char *input)
{
	int port = std::atoi(input);
	
	if (port < 0 || port > 65535)
		throw std::logic_error("Invalid port number");
	this->_port = port;	
}

void Server::setupTCP(void)
{
	const int	enable = 1;
	sockAddrIn	serverAddr;
	
	this->_serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_serverFd < 0)
		throw std::runtime_error("Failed to create socket");
	if (setsockopt(this->_serverFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		throw std::runtime_error("setsockopt failed");
	std::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(this->_port);
	if (bind(this->_serverFd, (sockAddr *) &serverAddr, sizeof(serverAddr)) < 0)
		throw std::runtime_error("Failed to bind to socket"); 
	int flags = fcntl(this->_serverFd, F_GETFL, 0);
	if (fcntl(this->_serverFd, F_SETFL, flags | O_NONBLOCK) == -1)
    	throw std::runtime_error("Failed to set socketFd to non-blocking");
	listen(this->_serverFd, CLIENT_LIMIT);
}

// void printBytes(const std::string& str) {
// 	for (size_t i = 0; i < str.size(); ++i) {
// 		std::cout << static_cast<int>(static_cast<unsigned char>(str[i])) << " ";
// 	}
// 	std::cout << std::endl;
// }

void Server::sigHandler(int)
{
	close(Server::_serverFd);
	throw std::runtime_error("\nServer stopped by SIGINT");
}

void	Server::mainLoop(void)
{
	std::vector<pollfd> fds;
	std::vector<Client> clients;

	signal(SIGINT, &Server::sigHandler);
	fds.push_back((pollfd) {.fd = this->_serverFd, .events = POLLIN});
	
	while (true)
	{
		int activity = poll(fds.data(), fds.size(), TIMEOUT);
		if (activity < 0)
		{
			ERROR("Poll error");
			continue;
		}
		if (fds.data()[0].revents & POLLIN)
		{
			Client newClient(this->_serverFd);
			fds.push_back((pollfd) { .fd = newClient.getFd(), .events = POLLIN});
			clients.push_back(newClient);
		}
		for (std::size_t i = 1; i < fds.size(); i++)
		{
			if (fds.data()[i].revents & POLLIN)
			{
				std::string data = receiveData(clients[i - 1]);
				std::vector<std::string> lines = split(data, "\r\n");
				for (std::vector<std::string>::iterator line = lines.begin(); line != lines.end(); line++)
				{
					if (*line == "")
						continue ;
					Message msg = parseMsg(*line);
					std::string response = processMessage(msg, clients[i - 1], clients);
					clients[i - 1].sendMessage(response);
				}
				if (clients[i - 1].getShouldEraseClient())
				{
					close(clients[i - 1].getFd());
					clients.erase(clients.begin() + i - 1);
					fds.erase(fds.begin() + i);
					Client::decrementIdCounter();
				}

			}
		}
			std::cout << "clients: " << clients.size() << std::endl;
		sleep(1); // Will be removed
	}
	return ;
}

std::string const Server::getPasswd(void)
{
	return (Server::_passwd);
}

void Server::setPasswd(char *passwd)
{
	Server::_passwd = std::string(passwd);
}