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
	std::string _key;
	bool		_i;
	bool		_t;
	bool		_k;
	bool		_l;

	std::vector<Client>	_clients;
	std::vector<Client>	_operators;
	size_t 				_userLimit;
	
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
	std::string getKey() const;
	void setKey(const std::string &key);
	void removeKey();
	void setTopicRestricted(bool action);
	bool getIsInviteOnly() const;
	void setIsInviteOnly(bool action);
	std::vector<Client> &getClients();
	const std::vector<Client> &getClients() const;
	void setClients(const std::vector<Client> &clients);
	size_t getUserLimit() const;
	void setUserLimit(const size_t &userLimit);
	std::string getChannelUsers();
	void addClient(const Client &client);
	void addOperator(const Client &client);
	void removeOperator(const Client &client);

	void removeClient(const Client &client);
	void removeClientLimit();

	bool isClientOnChannel(const Client &client);
	bool isClientOnChannel(const std::string &client);

	bool isOperator(Client &client);

	bool isTopicOPOnly();
	std::pair<std::string, std::string> getModes() const;
};

#endif
