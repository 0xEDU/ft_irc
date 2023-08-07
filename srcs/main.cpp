/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etachott < etachott@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:52:43 by etachott          #+#    #+#             */
/*   Updated: 2023/08/07 18:42:45 by etachott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#define BUFFER_SIZE 1024

// Will be subbed by a throw class
void exitError(std::string error) {
	std::cerr << "Error: " << error << std::endl;
	std::exit(1);
}

int main(int argc, char **argv) {
	if (argc < 3)
		exitError("No port or password!");
	
	int			sockfd, newsockfd, port, n;
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
		send(newsockfd, "Hello, world!\n", 13, 0);
		std::memset(buffer, 0, BUFFER_SIZE);
		
		n = read(newsockfd, buffer, BUFFER_SIZE - 1); // Use poll (or similiar) instead of read
		if (n < 0)
			exitError("Reading from socket failed!");
		std::cout << "The message is: " << buffer << std::endl;
		close(newsockfd);
		close(sockfd);
	}
	return (0);
}