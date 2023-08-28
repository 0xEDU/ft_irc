#include "Client.hpp"
#include "ft_irc.hpp"
#include "ft_irc.hpp"
int Client::_idCounter = 0;

Client::Client(void) : _fd(0), _id(0), _name(""), _nick("") {
}

Client::Client(int serverfd, pollfd pollfds[CLIENT_LIMIT])
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
	pollfds[this->_id].fd = this->_fd;
	return ;
}

Client::Client(const Client &rhs) {
	*this = rhs;
}

Client &Client::operator=(const Client &rhs) {
	this->_name = rhs._name;
	this->_nick = rhs._nick;
	this->_id = rhs._id;
	this->_fd = rhs._fd;

	return *this;
}

Client::~Client(void) {}

std::string const Client::getName(void) const
{
	return (this->_name);
}

void Client::setName(const std::string &name)
{
	this->_name = name;
}

std::string const Client::getNick(void) const
{
	return (this->_nick);
}

void Client::setNick(const std::string &nick)
{
	this->_nick = nick;
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

void Client::decrementIdCounter(void)
{
	_idCounter -= 1;
}