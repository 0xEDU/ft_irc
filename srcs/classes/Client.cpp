#include "ft_irc.hpp"

int Client::_idCounter = 0;

Client::Client() : _shouldEraseClient(false), _retries(0), _fd(0), _id(0), _isCommandComplete(false) {}

Client::Client(int serverfd) :
	_shouldEraseClient(false),
	_retries(0),
	_id(_idCounter),
	_isCommandComplete(false)
{
	sockAddrIn cliAddr;
	socklen_t cliLen = sizeof(cliAddr);

	this->_fd = accept(serverfd, (sockAddr *)&cliAddr, &cliLen);
	if (this->_fd < 0)
		throw std::runtime_error("Failed to accept client");
	if (fcntl(this->_fd, F_SETFL, O_NONBLOCK) == -1)
    	throw std::runtime_error("Failed to set socketFd to non-blocking");
	Client::_idCounter++;
	std::cout << "Number of clients connected: " << Client::_idCounter << std::endl <<  std::endl;
	this->_id = Client::_idCounter;
}

Client::Client(const Client &rhs) : _shouldEraseClient(), _retries(), _fd(), _id(), _isCommandComplete() {
	*this = rhs;
}

Client &Client::operator=(const Client &rhs) {
	if (&rhs != this) {
		this->_realName = rhs._realName;
		this->_nick = rhs._nick;
        this->_user = rhs._user;
		this->_id = rhs._id;
		this->_fd = rhs._fd;
		this->_pass = rhs._pass;
		this->_currCommand = rhs._currCommand;
		this->_isCommandComplete = rhs._isCommandComplete;
		this->_shouldEraseClient = rhs._shouldEraseClient;
		this->_retries = rhs._retries;
	}
	return *this;
}


Client::~Client() {}

std::string Client::getRealName() const
{
	return (this->_realName);
}

void Client::setRealName(const std::string &clientRealName)
{
	this->_realName = clientRealName;
}

std::string Client::getNick() const
{
	return (this->_nick);
}

void Client::setNick(const std::string &clientNick)
{
	this->_nick = clientNick;
}

std::string Client::getUser() const
{
	return (this->_user);
}

void Client::setUser(const std::string &clientUser)
{
	this->_user = clientUser;
}

int Client::getId() const
{
	return (this->_id);
}

void Client::setId(const int &id)
{
	this->_id = id;
}

int Client::getFd() const
{
	return (this->_fd);
}

void Client::setFd(const int &fd)
{
	this->_fd = fd;
}

int Client::getIdCounter()
{
	return (Client::_idCounter);
}

std::string Client::getPass() const
{
	return (this->_pass);
}

void Client::setPass(const std::string &clientpass)
{
	this->_pass = clientpass;
}

void Client::setShouldEraseClient(bool state)
{
	this->_shouldEraseClient = state;
}

bool Client::getShouldEraseClient() const
{
	return (this->_shouldEraseClient);
}

void Client::incrementRetries()
{
	this->_retries += 1;
}

int Client::getRetries() const
{
	return (this->_retries);
}

void Client::setRetries(int retries)
{
	this->_retries = retries;
}

void Client::decrementIdCounter()
{
	_idCounter -= 1;
	std::cout << "Number of clients connected: " << _idCounter << std::endl;
}

void Client::sendMessage(std::pair<std::string, std::vector<Client> > &msg) const
{
	if ((msg.first.empty() && msg.second.empty())
        || (_currCommand.find("PRIVMSG") == 0 && msg.second.empty()))
        return;
    std::vector<Client>::iterator it = msg.second.begin();
    if (msg.second.empty()) {
        if (send(this->_fd, msg.first.c_str(), msg.first.length(), 0) == -1)
            ERROR("Failed to send message to client")
        return ;
    }
    for (; it != msg.second.end(); it++) {
        if (send((*it)._fd, msg.first.c_str(), msg.first.length(), 0) == -1)
            ERROR("Failed to send message to client")
    }
}

bool Client::operator==(const Client &rhs) {
    return this->_user == rhs._user;
}

bool Client::operator==(const std::string &rhs) {
    return this->_user == rhs;
}

void Client::incrementCurrCommand(const std::string &cmd)
{
	this->_currCommand += cmd;
	std::size_t found = this->_currCommand.find("\r\n");
	if (found != std::string::npos)
		this->_isCommandComplete = true;
}

void Client::setCurrCommand(const std::string &cmd)
{
	this->_currCommand = cmd;
}

std::string Client::getCurrCommand() const
{
	return (this->_currCommand);
}

bool Client::getIsCommandComplete() const
{
	return (this->_isCommandComplete);
}

void Client::setIsCommandComplete(const bool &state)
{
	this->_isCommandComplete = state;
}

std::string Client::receiveData(Client &client)
{
    std::string data;

    char buff[BUFFER_SIZE];
    std::memset(buff, 0, BUFFER_SIZE);

    long nbytes = recv(client.getFd(), buff, BUFFER_SIZE, 0);
    if (nbytes == 0)
        client.setShouldEraseClient(true);
    else
        data.append(buff, nbytes);
    std::cout << "RECEIVED: " << data << std::endl;
    return data;
}