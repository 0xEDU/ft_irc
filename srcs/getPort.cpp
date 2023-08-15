/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getPort.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:53:46 by guribeir          #+#    #+#             */
/*   Updated: 2023/08/15 17:17:50 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int	getPort(char *input)
{
	int port = std::atoi(input);
	
	if (port < 0 || port > 65535)
		throw std::logic_error("Invalid port number");
	return (port);
}