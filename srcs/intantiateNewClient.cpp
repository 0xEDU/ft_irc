/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intantiateNewClient.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:04:04 by guribeir          #+#    #+#             */
/*   Updated: 2023/08/17 19:05:13 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void intantiateNewClient(int serverfd, int clientfd, pollfd pollfds[CLIENT_LIMIT])
{
	sockAddrIn cliAddr;
	socklen_t cliLen = sizeof(cliAddr);
	
	clientfd = accept(serverfd, (sockAddr *)&cliAddr, &cliLen);
	if (clientfd < 0)
		throw std::runtime_error("Failed to accept client");
	for (int i = 1; i < CLIENT_LIMIT; i++) {
		if (pollfds[i].fd == -1) {
			pollfds[i].fd = clientfd;
			break ;
		}
	}
}