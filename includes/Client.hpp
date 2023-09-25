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

	Client();
	Client(const Client &rhs);
	Client &operator=( const Client &rhs);
	explicit Client(int serverfd);
	~Client();
	
	int getId() const;
	void setId(const int &id);
	int getFd() const;
	void setFd(const int &fd);
	std::string getRealName() const;
	void setRealName(const std::string &name);
	std::string getUser() const;
	void setUser(const std::string &user);
	std::string getNick() const;
	void setNick(const std::string &nick);
	bool getShouldEraseClient() const;
	void setShouldEraseClient(bool state);
	int getRetries() const;
	void setRetries(int value);
	static int getIdCounter() ;

	static void decrementIdCounter();
	void sendMessage(std::pair<std::string, std::vector<Client> > &msg) const;
	void incrementRetries();

    bool operator==(const Client &rhs);
};

#endif