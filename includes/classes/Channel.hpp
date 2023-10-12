#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>
#include "ft_irc.hpp"

class Channel
{
	private:

	std::string _topic;
	std::string _name;
	std::string _password;
	bool		_i;
	bool		_t;
	bool		_k;
	bool		_l;

	bool 				_isInviteOnly;
	std::vector<Client>	_clients;
	std::vector<Client>	_operators;
	int 				_userLimit;
	
	public:

	Channel();
	explicit Channel(const std::string& name);
	~Channel();
	Channel(Channel const &src);
	Channel &operator=(Channel const &src);
	bool operator==(const std::string &name);

	std::string getTopic() const;
	void setTopic(const std::string &topic);
	std::string getName() const;
	void setName(const std::string &name);
	std::string getPassword() const;
	void setPassword(const std::string &password);
	bool getIsInviteOnly() const;
	void setIsInviteOnly(const bool &isInviteOnly);
	std::vector<Client> getClients() const;
	void setClients(const std::vector<Client> &clients);
	int getUserLimit() const;
	void setUserLimit(const int &userLimit);
	std::string getChannelUsers();
	void addClient(const Client &client);
	void addOperator(const Client &client);
	void removeOperator(const Client &client);

	void disconnectClient(const Client &client);

	bool isClientOnChannel(const Client &client);
	bool isClientOnChannel(const std::string &client);

	bool isOperator(Client &client);

	std::pair<std::string, std::string> getModes() const;
};

#endif