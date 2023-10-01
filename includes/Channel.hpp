#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>
#include "ft_irc.hpp"

class Channel
{
	private:

	std::string 		_topic;
	std::string 		_name;
	std::string 		_password;
	bool 				_isInviteOnly;
	std::vector<Client>	_clients;
    std::vector<Client>	_operators;
	int 				_userLimit;
	
	public:

	Channel(void);
	Channel(const std::string& name);
	~Channel(void);
	Channel(Channel const &src);
	Channel &operator=(Channel const &src);
	bool operator==(const std::string &name);

	void validateClientName(std::string name);
	
	std::string getTopic(void) const;
	void setTopic(const std::string &topic);
	std::string getName(void) const;
	void setName(const std::string &name);
	std::string getPassword(void) const;
	void setPassword(const std::string &password);
	bool getIsInviteOnly(void) const;
	void setIsInviteOnly(const bool &isInviteOnly);
	std::vector<Client> getClients(void) const;
	void setClients(const std::vector<Client> &clients);
	int getUserLimit(void) const;
	void setUserLimit(const int &userLimit);
    std::string getChannelUsers();
    void addClient(const Client &client);
    void addOperator(const Client &client);

    void disconnectClient(const Client &client);

    bool isClientOnChannel(const Client &client);
};

#endif