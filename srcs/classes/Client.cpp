#include "ft_irc.hpp"

int Client::_idCounter = 0;

Client::Client(int socketDescriptor) :
	_shouldEraseClient(false),
	_retries(0),
	_fd(socketDescriptor)
{
	Client::_idCounter++;
	this->_id = Client::_idCounter;
	std::cout << "Number of clients connected: " << Client::_idCounter << std::endl;
}

Client::Client(const Client &rhs) : _shouldEraseClient(), _retries(), _fd(), _id() {
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
		this->_rawData = rhs._rawData;
		this->_buffer = rhs._buffer;
		this->_commandsQueue = rhs._commandsQueue;
		this->_shouldEraseClient = rhs._shouldEraseClient;
		this->_retries = rhs._retries;
		this->_channelsInvited = rhs._channelsInvited;
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
	LOG("Number of clients connected: " << _idCounter)
}
void Client::addChannelToInvited(const std::string &channelName) {
	this->_channelsInvited.push_back(channelName);
}

std::vector<std::string> &Client::getChannelInvited() {
	return this->_channelsInvited;
}

bool Client::channelOnInviteList(const std::string &channelName) {
	return std::find(
		this->_channelsInvited.begin(), this->_channelsInvited.end(), channelName
	) != this->_channelsInvited.end();
}

void Client::removeChannelFromInviteList(const std::string &channelName) {
	std::vector<std::string>::iterator it = std::find(
		this->_channelsInvited.begin(), this->_channelsInvited.end(), channelName
	);
	this->_channelsInvited.erase(it);
}

void Client::sendReply(std::pair<std::string, std::vector<Client> > &msg) const
{

	if ((msg.first.empty() && msg.second.empty()))
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

void Client::sendToBroadcastOnly(std::pair<std::string, std::vector<Client> > &msg)
{
	if ((msg.first.empty() && msg.second.empty()))
		return;
	std::vector<Client>::iterator it = msg.second.begin();
	for (; it != msg.second.end(); it++) {
		if (send((*it)._fd, msg.first.c_str(), msg.first.length(), 0) == -1)
			ERROR("Failed to send message to client")
	}
}

bool Client::operator==(const Client &rhs) {
	return this->_user == rhs._user;
}

bool Client::operator==(const std::string &rhs) {
	return this->_user == rhs || this->_nick == rhs;
}

void Client::storeRawData(const std::string &data)
{
	this->_rawData = data;
}

std::string Client::getRawData() const
{
	return (this->_rawData);
}

std::queue<std::string> &Client::getCommandsQueue() {
	return (this->_commandsQueue);
};

bool Client::isAuthenticated() const {
	if (this->_user.empty()
		|| this->_nick.empty()
		|| this->_pass.empty())
		return false;
	return true;
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
	LOG("RECEIVED: >>" << data << "<<")
	return data;
}

void Client::flushBuffer() {
	this->_buffer.clear();
}

void Client::pushToCommandQueue() {
	this->_buffer.append(_rawData);
	if (this->_buffer.empty())
		return ;
	std::vector<std::string> commands = Utils::split(this->_buffer, CRLF);
	bool commandIsComplete = (_rawData.size() >= 2
		&& this->_rawData[_rawData.size() - 2] == '\r'
		&& this->_rawData[_rawData.size() - 1] == '\n');
	if (!commandIsComplete) {
		this->_buffer = commands.back();
		commands.pop_back();
	} else {
		this->_buffer.clear();
	}
	for (std::vector<std::string>::iterator command = commands.begin(); command != commands.end(); command++) {
		this->_commandsQueue.push(*command);
	}
}
