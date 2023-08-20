#include "ft_irc.hpp"

// CAP ...
// PASS senha

//construtor do cliente??
Client instantiateNewClient(int serverfd, int clientfd, pollfd pollfds[CLIENT_LIMIT])
{
	sockAddrIn cliAddr;
	socklen_t cliLen = sizeof(cliAddr);
	
	clientfd = accept(serverfd, (sockAddr *)&cliAddr, &cliLen);
	if (clientfd < 0)
		throw std::runtime_error("Failed to accept client");
	Client client(clientfd);
	pollfds[client.getId()].fd = clientfd;
	/* for (int i = 1; i < CLIENT_LIMIT; i++) { */
	/* 	if (pollfds[i].fd == -1) { */
	/* 		pollfds[i].fd = clientfd; */
	/* 		break ; */
	/* 	} */
	/* } */
	
	bool validClient = registerClient(client);
	(void)validClient;
	return (client);
}