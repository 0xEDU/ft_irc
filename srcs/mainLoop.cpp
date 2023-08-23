#include "ft_irc.hpp"

int serverfd, clientfd;

//close all fds from pollfds; same on QUIT cmd
static void sigHandler(int)
{
	close(serverfd);
	close(clientfd);
	throw std::runtime_error("\nServer stopped by SIGINT");
}

static void initPollfds(pollfd pollfds[])
{
	std::memset(pollfds, 0, sizeof(pollfd) * CLIENT_LIMIT);
	for (int i = 0; i < CLIENT_LIMIT; i++)
	{
		pollfds[i].fd = -1;
		pollfds[i].events = POLLIN;
	}
	pollfds[0].fd = serverfd;
}

void	mainLoop(int sockfd)
{
	pollfd pollfds[CLIENT_LIMIT];
	std::vector<Client> clients;

	serverfd = sockfd;
	signal(SIGINT, &sigHandler);
	initPollfds(pollfds);
	while (true)
	{
		int activity = poll(pollfds, CLIENT_LIMIT, TIMEOUT);
		if (activity < 0)
		{
			ERROR("Poll error");
			continue;
		}
		if (pollfds[0].revents & POLLIN)
		{
			Client newClient(serverfd, pollfds);
			//std::cout << "New client: \n" << newClient << std::endl;
			if (validateClient(newClient))
				clients.push_back(newClient);
		}
		for (int i = 1; i < CLIENT_LIMIT; i++)
		{
			if (pollfds[i].revents & POLLIN)
				treatClientMessage(pollfds[i].fd);
		}
		std::cout << "clients: " << clients.size() << std::endl;
		
		for (size_t i = 0; i < clients.size(); i++)
		{
			std::cout << "Nick: " << clients[i].getNick() << std::endl;
			std::cout << "Name: " << clients[i].getName() << std::endl;
			std::cout << "Fd: " << clients[i].getFd() << std::endl;
			std::cout << "Id: " << clients[i].getId() << std::endl;
			std::cout << "IdCounter: " << clients[i].getIdCounter() << std::endl;
		}
		sleep(1); // Will be removed
	}
	return ;
}