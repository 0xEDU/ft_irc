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
	
	int			port, n;
	socklen_t	clientLen;
	char		buffer[BUFFER_SIZE];
	SockaddrIn	servAddr, clientAddr;
		
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		exitError("Can't open new socket!");
	std::memset((char *)&servAddr, 0, sizeof(servAddr));
	port = std::atoi(argv[1]); // Do port validation ;-;
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = INADDR_ANY;
	servAddr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *)&servAddr,
		sizeof(servAddr)) < 0)
		exitError("Binding failed!");
	listen(sockfd, 5); // 5 is the max size of the backlog queue for listen
	clientLen = sizeof(clientAddr);
	while (true) {
		newsockfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientLen);
		if (newsockfd < 0)
			exitError("Accept failed!");
		std::cout << "Server got connection from "
			<< inet_ntoa(clientAddr.sin_addr)
			<< " port " << ntohs(clientAddr.sin_port)
			<< std::endl;
		std::string serverName = "TROLL IRC";
		std::string welcomeMsg = ":myserver 001 yournick :Welcome to the IRC server!\r\n";
		std::string yourHostMsg = ":myserver 002 yournick :Your host is " + serverName + "\r\n";
		std::string createdMsg = ":myserver 003 yournick :This server was created sometime\r\n";
		std::string myInfoMsg = ":myserver 004 yournick " + serverName + " ircd-0.1 aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ0123456789\r\n";
		std::string helloos = "Hello, World!\r\n";

		send(newsockfd, welcomeMsg.c_str(), welcomeMsg.length(), 0);
		send(newsockfd, yourHostMsg.c_str(), yourHostMsg.length(), 0);
		send(newsockfd, createdMsg.c_str(), createdMsg.length(), 0);
		send(newsockfd, myInfoMsg.c_str(), myInfoMsg.length(), 0);
		send(newsockfd, helloos.c_str(), helloos.length(), 0);
		std::string hello = std::string(":ft_irc 001 GOD :Hello, world!\r\n");
		send(newsockfd, hello.c_str(), hello.length(), 0);
		std::memset(buffer, 0, BUFFER_SIZE);
		
		char rcv[1024];
		int j = recv(newsockfd, rcv, 1024, MSG_DONTWAIT);
		n = read(newsockfd, buffer, BUFFER_SIZE - 1); // Use poll (or similiar) instead of read
		if (n < 0)
			exitError("Reading from socket failed!");
		std::cout << "The message is: " << buffer << std::endl;
	}
	return (0);
}