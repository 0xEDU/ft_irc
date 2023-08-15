/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setupTCP.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:05:31 by guribeir          #+#    #+#             */
/*   Updated: 2023/08/15 19:42:21 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

inline static
void initServAddr(sockAddrIn &servAddr, int port)
{
	std::memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET; 
	servAddr.sin_addr.s_addr = INADDR_ANY;
	servAddr.sin_port = htons(port);
}

int setupTCP(int port)
{
	const int	enable = 1;
	int			sockfd;
	sockAddrIn	servAddr;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int flags = fcntl(sockfd, F_GETFL, 0);
	if (sockfd < 0)
		throw std::runtime_error("Failed to connect to socket");
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		throw std::runtime_error("setsockopt failed");
	initServAddr(servAddr, port);
	if (bind(sockfd, (sockAddr *) &servAddr, sizeof(servAddr)) < 0)
		throw std::runtime_error("Failed to bind to socket"); 
	if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1)
    	throw std::runtime_error("Failed to set sockfd to non-blocking");
	listen(sockfd, CLIENT_LIMIT);
	return (sockfd);
}