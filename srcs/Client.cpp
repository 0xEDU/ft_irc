#include "ft_irc.hpp"

int Client::_idCounter = 0;

Client::Client(void) : _shouldEraseClient(0), _retriesNick(0), _fd(0), _id(0), _realName(""), _nick("") {
}

Client::Client(int serverfd)
{
	sockAddrIn cliAddr;
	socklen_t cliLen = sizeof(cliAddr);

	this->_fd = accept(serverfd, (sockAddr *)&cliAddr, &cliLen);
	if (this->_fd < 0)
		throw std::runtime_error("Failed to accept client");
	int flags = fcntl(this->_fd, F_GETFL, 0);
	if (fcntl(this->_fd, F_SETFL, flags | O_NONBLOCK) == -1)
    	throw std::runtime_error("Failed to set socketFd to non-blocking");
	this->_idCounter++;
	this->_id = this->_idCounter;
	this->_nick = "";
	this->_realName = "";
	this->_user = "";
	this->_retriesNick = 0;
	this->_shouldEraseClient = 0;
	return ;
}

Client::Client(const Client &rhs) {
	*this = rhs;
}

Client &Client::operator=(const Client &rhs) {
	this->_realName = rhs._realName;
	this->_nick = rhs._nick;
	this->_id = rhs._id;
	this->_fd = rhs._fd;

	return *this;
}

Client::~Client(void) {}

std::string const Client::getRealName(void) const
{
	return (this->_realName);
}

void Client::setRealName(const std::string &clientRealName)
{
	this->_realName = clientRealName;
}

std::string const Client::getNick(void) const
{
	return (this->_nick);
}

void Client::setNick(const std::string &clientNick)
{
	this->_nick = clientNick;
}

std::string const Client::getUser(void) const
{
	return (this->_user);
}

void Client::setUser(const std::string &clientUser)
{
	this->_user = clientUser;
}

int Client::getId(void) const
{
	return (this->_id);
}

void Client::setId(const int &id)
{
	this->_id = id;
}

int Client::getFd(void) const
{
	return (this->_fd);
}

void Client::setFd(const int &fd)
{
	this->_fd = fd;
}

int Client::getIdCounter(void) const
{
	return (this->_idCounter);
}

void Client::setShouldEraseClient(int state)
{
	this->_shouldEraseClient = state;
}

int Client::getShouldEraseClient(void)
{
	return(this->_shouldEraseClient);
}

void Client::incrementRetriesNick(void)
{
	this->_retriesNick += 1;
}

int Client::getRetriesNick(void)
{
	return(this->_retriesNick);
}


void Client::decrementIdCounter(void)
{
	_idCounter -= 1;
}

void Client::sendMessage(std::string &msg)
{
	if (msg != "")
	{
		if (send(this->_fd, msg.c_str(), msg.length(), 0) == -1)
			ERROR("Failed to send message to client")
	}
}