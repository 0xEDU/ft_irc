/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:22:00 by guribeir          #+#    #+#             */
/*   Updated: 2023/08/17 19:54:17 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client
{
	private:
	
	static int _idCounter;
	
	protected:

	int _fd;
	int _id;
	std::string _name;
	std::string _nick;
	
	public:

	Client(void);
	Client(int fd);
	~Client(void);
	
	int const getId(void) const;
	void setId(const int &id);
	int const getFd(void) const;
	void setFd(const int &fd);
	std::string const getName(void) const;
	void setName(const std::string &name);
	std::string const getNick(void) const;
	void setNick(const std::string &nick);
};

#endif