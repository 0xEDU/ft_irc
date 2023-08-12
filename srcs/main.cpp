/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:52:43 by etachott          #+#    #+#             */
/*   Updated: 2023/08/11 18:21:25 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#define BUFFER_SIZE 512

int sockfd, newsockfd;

// Will be subbed by a throw class
void exitError(std::string error) {
	std::cerr << "Error: " << error << std::endl;
	std::cerr << "Also: " << errno << std::endl;
	std::exit(1);
}

//function to handle signal Ctrl + c to proper quit
void signalHandler(int signum) {
	close(newsockfd);
	close(sockfd);
	exit(signum);
}

int main(int argc, char **argv) {
	signal(SIGINT, signalHandler);
	if (argc < 3)
		exitError("No port or password!");
	
	int			port,
				opt = 1;
	socklen_t	clientLen;
	SockaddrIn	servAddr, clientAddr;
		
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		exitError("Can't open new socket!");
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT,
               &opt, sizeof(opt)) < 0)
		exitError("Failed to set SO_REUSEPORT.");
	std::memset((char *)&servAddr, 0, sizeof(servAddr));
	port = std::atoi(argv[1]); // Do port validation ;-;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = INADDR_ANY;
	servAddr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
		exitError("Binding failed!");
	listen(sockfd, 5); // 5 is the max size of the backlog queue for listen
	clientLen = sizeof(clientAddr);
	struct pollfd fds[CLIENT_LIMIT]; // Define CLIENT_LIMIT as the maximum number of connections you want to support
	for (int i = 0; i < CLIENT_LIMIT; i++) {
		fds[i].fd = -1; // Initialize all file descriptors to -1
		fds[i].events = POLLIN; // We're interested in read events
	}
	fds[0].fd = sockfd; // First file descriptor is the listening socket
	std::cout << "FT_IRC v0.1" << std::endl;
	while (true) {
		int activity = poll(fds, CLIENT_LIMIT, TIMEOUT); // TIMEOUT in milliseconds or -1 to wait indefinitely

		if (activity < 0) {
			std::cerr << "Error: Poll error\n";
			continue;
		}

		if (fds[0].revents & POLLIN) {
			// New connection on the listening socket
			newsockfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientLen);
			if (newsockfd < 0) {
				std::cerr << "Error: Accept failed\n";
				continue;
			}

			// Add newsockfd to the fds array
			for (int i = 1; i < CLIENT_LIMIT; i++) {
				if (fds[i].fd == -1) {
					fds[i].fd = newsockfd;
					break;
				}
			}
		}

		// Check for events on client sockets
		for (int i = 1; i < CLIENT_LIMIT; i++) {
			if (fds[i].fd != -1 && (fds[i].revents & POLLIN)) {
				char *bfr = new char[BUFFER_SIZE];
				std::memset(bfr, 0, BUFFER_SIZE);
				read(fds[i].fd, bfr, BUFFER_SIZE);
				std::string msg(bfr);
				delete[] bfr;
				/* std::cout << msg; */
				if (msg.find("USER") != std::string::npos) {
					std::cout << "Client connected!" << std::endl;
					std::string response1(":127.0.0.1 001 edu :THIS IS FT_IRC edu!edu@127.0.0.1\r\n"); // Check for repeated names
					send(fds[i].fd, response1.c_str(), response1.length(), 0);
				}
				if (std::strncmp(msg.c_str(), "JOIN", 4) == 0) {
					std::string response1("edu JOIN :fuba\r\n");
					std::string response2("ircserv #fuba :FT edu #fuba :FT\r\n");
					std::string response3("ircserv reply edu = #fuba : edua eduar\r\n:ircserv asdf edu #fuba :fodase\r\n");
					send(fds[i].fd, response1.c_str(), response1.length(), 0);
					send(fds[i].fd, response2.c_str(), response2.length(), 0);
					send(fds[i].fd, response3.c_str(), response3.length(), 0);
				}

				// If the client closed the connection, close the socket and set fd to -1
				if (msg.find("QUIT") != std::string::npos) {
					std::cout << "Client disconnected!" << std::endl;
					close(newsockfd);
				}
			}
		}
    }
	return (0);
}
