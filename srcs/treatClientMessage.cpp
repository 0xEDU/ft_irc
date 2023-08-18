/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatClientMessage.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:07:21 by guribeir          #+#    #+#             */
/*   Updated: 2023/08/18 17:46:00 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void treatClientMessage(int currClientfd)
{
	char buff[BUFFER_SIZE];
	std::memset(buff, 0, BUFFER_SIZE);
	if (recv(currClientfd, buff, BUFFER_SIZE, 0) < 0)
		throw std::runtime_error("Failed to receive message");
	LOG(buff)
	std::exit(1);
}



