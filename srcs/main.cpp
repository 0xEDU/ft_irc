/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:52:43 by etachott          #+#    #+#             */
/*   Updated: 2023/08/18 16:57:09 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc != 3)
			throw std::logic_error("Usage: ./ircserv <port> <password>");
		int port = getPort(argv[1]);
		int sockfd = setupTCP(port);
		//em algum momento precisamos criar a senha.
		mainLoop(sockfd);
	}
	catch(const std::exception& e)
	{
		ERROR(e.what());
	}
	
	return (0);
}
