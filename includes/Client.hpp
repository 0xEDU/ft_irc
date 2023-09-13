#pragma once
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include "ft_irc.hpp"

class Client
{
	private:
	
	bool _shouldEraseClient;
	int _retries;
	static int _idCounter;

	protected:

	int _fd;
	int _id;
	std::string _realName;
	std::string _nick;
	std::string _user;
	
	public:

	Client(void);
	Client(const Client &rhs);
	Client &operator=( const Client &rhs);
	Client(int serverfd);
	~Client(void);
	
	int getId(void) const;
	void setId(const int &id);
	int getFd(void) const;
	void setFd(const int &fd);
	std::string const getRealName(void) const;
	void setRealName(const std::string &name);
	std::string const getUser(void) const;
	void setUser(const std::string &user);
	std::string const getNick(void) const;
	void setNick(const std::string &nick);
	bool getShouldEraseClient(void);
	void setShouldEraseClient(bool state);
	int getRetries(void);
	void setRetries(int value);
	int getIdCounter(void) const;

	static void decrementIdCounter(void);
	void sendMessage(std::string &msg);
	void incrementRetries(void);
};

#endif