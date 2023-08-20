#include "ft_irc.hpp"

int serverfd, clientfd;

//close all fds from pollfds; same on QUIT cmd
static void sigHandler(int)
{
	close(serverfd);
	close(clientfd);
	throw std::runtime_error("\nServer stopped by SIGINT");
}

// static std::ostream &operator<<(std::ostream &os, pollfd pollfds[CLIENT_LIMIT])
// {
// 	for (int i = 0; i < CLIENT_LIMIT; i++)
// 	{
// 		if (pollfds[i].fd == -1)
// 			continue;
// 		os << "fd = " << pollfds[i].fd << " | revents = " << pollfds[i].revents << " ||";
// 	}
// 	return os;
// }

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
			clients.push_back(intantiateNewClient(serverfd, clientfd, pollfds));
		for (int i = 1; i < CLIENT_LIMIT; i++)
		{
			if (pollfds[i].revents & POLLIN)
				treatClientMessage(pollfds[i].fd);
		}
	}
	return ;
}