#include "ft_irc.hpp"

int serverfd, clientfd;

//close all fds from pollfds; same on QUIT cmd
static void sigHandler(int)
{
	close(serverfd);
	close(clientfd);
	throw std::runtime_error("\nServer stopped by SIGINT");
}

void	mainLoop(int sockfd)
{
	std::vector<pollfd> fds;
	std::vector<Client> clients;

	serverfd = sockfd;
	signal(SIGINT, &sigHandler);
	fds.push_back((pollfd) {.fd = serverfd, .events = POLLIN});
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
			Client newClient(serverfd, fds.data());
			fds.push_back((pollfd) { .fd = newClient.getFd(), .events = POLLIN});
			clients.push_back(newClient);
		}
		for (std::size_t i = 1; i < fds.size(); i++)
		{
			if (fds.data()[i].revents & POLLIN)
				std::string data = receiveData(clients[i - 1]);
		}
		std::cout << "clients: " << clients.size() << std::endl;
		
		// for (size_t i = 0; i < clients.size(); i++)
		// {
		// 	std::cout << "Nick: " << clients[i].getNick() << std::endl;
		// 	std::cout << "Name: " << clients[i].getName() << std::endl;
		// 	std::cout << "Fd: " << clients[i].getFd() << std::endl;
		// 	std::cout << "Id: " << clients[i].getId() << std::endl;
		// 	std::cout << "IdCounter: " << clients[i].getIdCounter() << std::endl;
		// }
		sleep(1); // Will be removed
	}
	return ;
}