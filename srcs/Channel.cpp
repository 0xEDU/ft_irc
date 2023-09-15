#include "ft_irc.hpp"

Channel::Channel(void) : _topic(""), _name(""), _password(""), _isInviteOnly(false), _clients(std::vector<Client>()), _userLimit(-1) {}

Channel::Channel(std::string name) : _topic(""), _name(name), _password(""), _isInviteOnly(false), _clients(std::vector<Client>()), _userLimit(-1) {}

Channel::~Channel(void) {}

Channel::Channel(Channel const &src)
{
	*this = src;
}

Channel &Channel::operator=(Channel const &src)
{
	if (this != &src)
	{
		this->_topic = src._topic;
		this->_name = src._name;
		this->_password = src._password;
		this->_isInviteOnly = src._isInviteOnly;
		this->_clients = src._clients;
		this->_userLimit = src._userLimit;
	}
	return (*this);
}

bool Channel::operator==(const std::string &name)
{
	if (name == this->_name)
		return true;
	return false;
}

std::string const Channel::getTopic(void) const
{
	return (this->_topic);
}

void Channel::setTopic(const std::string &topic)
{
	this->_topic = topic;
}

std::string const Channel::getName(void) const
{
	return (this->_name);
}

void Channel::setName(const std::string &name)
{
	this->_name = name;
}

std::string const Channel::getPassword(void) const
{
	return (this->_password);
}

void Channel::setPassword(const std::string &password)
{
	this->_password = password;
}

bool Channel::getIsInviteOnly(void) const
{
	return (this->_isInviteOnly);
}

void Channel::setIsInviteOnly(const bool &isInviteOnly)
{
	this->_isInviteOnly = isInviteOnly;
}

std::vector<Client> const Channel::getClients(void) const
{
	return (this->_clients);
}

void Channel::setClients(const std::vector<Client> &clients)
{
	this->_clients = clients;
}

int Channel::getUserLimit(void) const
{
	return (this->_userLimit);
}

void Channel::setUserLimit(const int &userLimit)
{
	this->_userLimit = userLimit;
}

void Channel::addClient(const Client &client)
{
	this->_clients.push_back(client);
}