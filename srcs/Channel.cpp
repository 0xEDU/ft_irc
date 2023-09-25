#include "ft_irc.hpp"
#include "Channel.hpp"


Channel::Channel() : _isInviteOnly(false), _clients(std::vector<Client>()), _userLimit(-1) {}

Channel::Channel(const std::string& name) : _name(name), _isInviteOnly(false), _clients(std::vector<Client>()), _userLimit(-1) {}

Channel::~Channel() {}

Channel::Channel(Channel const &src) : _isInviteOnly(), _userLimit()
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
        this->_operators = src._operators;
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

std::string Channel::getTopic() const
{
	return (this->_topic);
}

void Channel::setTopic(const std::string &topic)
{
	this->_topic = topic;
}

std::string Channel::getName() const
{
	return (this->_name);
}

void Channel::setName(const std::string &name)
{
	this->_name = name;
}

std::string Channel::getPassword() const
{
	return (this->_password);
}

void Channel::setPassword(const std::string &password)
{
	this->_password = password;
}

bool Channel::getIsInviteOnly() const
{
	return (this->_isInviteOnly);
}

void Channel::setIsInviteOnly(const bool &isInviteOnly)
{
	this->_isInviteOnly = isInviteOnly;
}

std::vector<Client> Channel::getClients() const
{
	return (this->_clients);
}

void Channel::setClients(const std::vector<Client> &clients)
{
	this->_clients = clients;
}

int Channel::getUserLimit() const
{
	return (this->_userLimit);
}

void Channel::setUserLimit(const int &userLimit)
{
	this->_userLimit = userLimit;
}

// Const talvez dê merda
void Channel::addClient(const Client &client)
{
	this->_clients.push_back(client);
}

std::string Channel::getChannelUsers() {
    std::string channelUsers;

    for (size_t i = 0; i < this->_clients.size(); i++) {
        if (std::find(this->_operators.begin(), this->_operators.end(), this->_clients[i]) != this->_operators.end())
            channelUsers += "@";
        channelUsers += this->_clients[i].getUser();
        channelUsers += " ";
    }
    return channelUsers;
}

void Channel::addOperator(const Client &client) {
    this->_operators.push_back(client);
}
