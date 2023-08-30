#include "ft_irc.hpp"

Channel::Channel(void) : _topic(""), _name(""), _password(NULL), _isInviteOnly(false), _clients(std::vector<Client>()), _userLimit(NULL) {}

Channel::Channel(std::string name) : _name(name) {}

Channel::~Channel(void)
{
	if (this->_password)
		delete this->_password;
	if (this->_userLimit)
		delete this->_userLimit;
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
	return (*this->_password);
}

void Channel::setPassword(const std::string &password)
{
	this->_password = new std::string(password);
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
	return (*this->_userLimit);
}

void Channel::setUserLimit(const int &userLimit)
{
	this->_userLimit = new int(userLimit);
}

