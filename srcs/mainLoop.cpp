#include "ft_irc.hpp"

int serverfd, clientfd;

void printBytes(const std::string& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        std::cout << static_cast<int>(static_cast<unsigned char>(str[i])) << " ";
    }
    std::cout << std::endl;
}

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
			{
				std::string data = receiveData(clients[i - 1]);
				std::vector<std::string> lines = split(data, "\r\n");
				for (std::vector<std::string>::iterator line = lines.begin(); line != lines.end(); line++)
				{
					Message msg = parseMsg(*line);
					std::string response = processMessage(msg, clients[i - 1], clients);
					clients[i - 1].sendMessage(response);
				}
				// if ("campoficouvazio")
				// {
				// 	clients.pop_back();
				// 	Client::decrementIdCounter();
				// }

			}
		}
			std::cout << "clients: " << clients.size() << std::endl;
		sleep(1); // Will be removed
	}
	return ;
}