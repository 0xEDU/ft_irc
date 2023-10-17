#pragma once
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ft_irc.hpp"

class Client
{
	private:
	
	bool _shouldEraseClient;
	int _retries;
	static int _idCounter;
	int _fd;
	int _id;
	std::string _realName;
	std::string _nick;
	std::string _user;
	std::string _currCommand;
	std::string _pass;
	bool _isCommandComplete;
	
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
	std::string getPass() const;
	void setPass(const std::string &clientpass);
	bool getShouldEraseClient() const;
	void setShouldEraseClient(bool state);
	int getRetries() const;
	void setRetries(int value);
	static int getIdCounter();
	void incrementCurrCommand(const std::string &cmd);
	void setCurrCommand(const std::string &cmd);
	std::string getCurrCommand() const;
	bool getIsCommandComplete() const;
	void setIsCommandComplete(const bool &state);

	static void decrementIdCounter();
	void sendMessage(std::pair<std::string, std::vector<Client> > &msg) const;
	void incrementRetries();

	bool operator==(const Client &rhs);
	bool operator==(const std::string &rhs);

	static std::string receiveData(Client &client);
	
	bool isAuthenticated(void) const;
};

#endif
