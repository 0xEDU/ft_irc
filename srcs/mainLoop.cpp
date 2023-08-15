/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainLoop.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:40:36 by guribeir          #+#    #+#             */
/*   Updated: 2023/08/15 19:50:30 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int serverfd, clientfd;

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
	sockAddrIn cliAddr;
	socklen_t cliLen = sizeof(cliAddr);

	serverfd = sockfd;
	signal(SIGINT, &sigHandler);
	initPollfds(pollfds);
	while (true)
	{
		int activity = poll(pollfds, CLIENT_LIMIT, TIMEOUT);
		if (activity < 0) {
			ERROR("Poll error");
			continue;
		}
		if (pollfds[0].revents & POLLIN)
		{
			clientfd = accept(serverfd, (sockAddr *)&cliAddr, &cliLen);
			if (clientfd < 0)
				throw std::runtime_error("Failed to accept client");
		}
		LOG(activity);
	}
	return ;
}