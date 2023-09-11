#pragma once
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include "ft_irc.hpp"

class Client
{
	private:
	
	int _shouldEraseClient;
	int _retriesNick;
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
	Client(int serverfd, pollfd pollfds[CLIENT_LIMIT]);
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
	int getIdCounter(void) const;
	void setShouldEraseClient(int state);
	int getShouldEraseClient(void);
	int getRetriesNick(void);

	static void decrementIdCounter(void);
	void sendMessage(std::string &msg);
	void incrementRetriesNick(void);
};

#endif