/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:45:41 by guribeir          #+#    #+#             */
/*   Updated: 2023/08/17 20:04:33 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>
#include "Client.hpp"

class Channel
{
	private:

	std::string _topic;
	std::string _name;
	std::string *_password;
	bool _isInviteOnly;
	std::vector<Client> _clients;
	int *_userLimit;
	
	public:

	Channel(void);
	Channel(std::string name);
	~Channel(void);

	void validateClientName(std::string name);
	
	std::string const getTopic(void) const;
	void setTopic(const std::string &topic);
	std::string const getName(void) const;
	void setName(const std::string &name);
	std::string const getPassword(void) const;
	void setPassword(const std::string &password);
	bool const getIsInviteOnly(void) const;
	void setIsInviteOnly(const bool &isInviteOnly);
	std::vector<Client> const getClients(void) const;
	void setClients(const std::vector<Client> &clients);
	int const getUserLimit(void) const;
	void setUserLimit(const int &userLimit);
	
};

#endif