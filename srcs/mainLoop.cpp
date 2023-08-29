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
				std::vector<std::string> lines = split(data, "\n");
				for (std::vector<std::string>::iterator line = lines.begin(); line != lines.end(); line++)
				{
					Message msg = parseMsg(line);
					processMessage(msg);
				//	if (isValidMessage(m)):
				//	  sendResponse(m);
				}
		}
		std::cout << "clients: " << clients.size() << std::endl;
		sleep(1); // Will be removed
	}
	return ;
}