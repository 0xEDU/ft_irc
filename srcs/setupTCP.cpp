#include "ft_irc.hpp"

inline static
void initServerAddr(sockAddrIn &serverAddr, int port)
{
	std::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET; 
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);
}

int setupTCP(int port)
{
	const int	enable = 1;
	int			socketFd;
	sockAddrIn	serverAddr;
	
	socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFd < 0)
		throw std::runtime_error("Failed to create socket");
	if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		throw std::runtime_error("setsockopt failed");
	initServerAddr(serverAddr, port);
	if (bind(socketFd, (sockAddr *) &serverAddr, sizeof(serverAddr)) < 0)
		throw std::runtime_error("Failed to bind to socket"); 
	/* int flags = fcntl(socketFd, F_GETFL, 0); */
	/* if (fcntl(serverfd, F_SETFL, flags | O_NONBLOCK) == -1) */
    	/* throw std::runtime_error("Failed to set socketFd to non-blocking"); */
	listen(socketFd, CLIENT_LIMIT);
	return (socketFd);
}