/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 19:25:51 by guribeir          #+#    #+#             */
/*   Updated: 2023/08/17 20:00:48 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

int Client::_idCounter = 0;

Client::Client(void) : _fd(0), _id(0), _name(""), _nick("") {}

Client::Client(int fd) : _fd(fd) 
{
	this->_idCounter++;
	this->_id = this->_idCounter;
	return ;
}

Client::~Client(void) {}

std::string const Client::getName(void) const
{
	return (this->_name);
}

void Client::setName(const std::string &name)
{
	this->_name = name;
}

std::string const Client::getNick(void) const
{
	return (this->_nick);
}

void Client::setNick(const std::string &nick)
{
	this->_nick = nick;
}

int const Client::getId(void) const
{
	return (this->_id);
}

void Client::setId(const int &id)
{
	this->_id = id;
}

int const Client::getFd(void) const
{
	return (this->_fd);
}

void Client::setFd(const int &fd)
{
	this->_fd = fd;
}