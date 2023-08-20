#include "ft_irc.hpp"

Client intantiateNewClient(int serverfd, int clientfd, pollfd pollfds[CLIENT_LIMIT])
{
	sockAddrIn cliAddr;
	socklen_t cliLen = sizeof(cliAddr);
	
	clientfd = accept(serverfd, (sockAddr *)&cliAddr, &cliLen);
	if (clientfd < 0)
		throw std::runtime_error("Failed to accept client");
	for (int i = 1; i < CLIENT_LIMIT; i++) {
		if (pollfds[i].fd == -1) {
			pollfds[i].fd = clientfd;
			break ;
		}
	}
	return (Client(clientfd));
}