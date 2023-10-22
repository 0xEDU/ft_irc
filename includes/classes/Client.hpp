#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ft_irc.hpp"

class Client
{
	private:
	
	bool _shouldEraseClient;
	int _retries;
	static int _idCounter;
	int _fd;
	int _id;
	std::string _realName;
	std::string _nick;
	std::string _user;
	std::string _rawData;
	std::string _pass;

	pollfd &_pollfdRef;

	std::queue<std::string> _commandsQueue;
	std::string _buffer;
	public:

	// Client();
	explicit Client(int serverfd, pollfd &pollfdRef);
	Client(const Client &rhs);
	Client &operator=( const Client &rhs);
	~Client();
	
	// GETTERS AND SETTERS
	int getId() const;
	void setId(const int &id);
	int getFd() const;
	void setFd(const int &fd);
	std::string getRealName() const;
	void setRealName(const std::string &name);
	std::string getUser() const;
	void setUser(const std::string &user);
	std::string getNick() const;
	void setNick(const std::string &nick);
	std::string getPass() const;
	void setPass(const std::string &clientpass);
	bool getShouldEraseClient() const;
	void setShouldEraseClient(bool state);
	int getRetries() const;
	void setRetries(int value);
	static int getIdCounter();
	void storeRawData(const std::string &cmd);
	void flushRawData();
	std::string getRawData() const;
	std::queue<std::string> &getCommandsQueue();
	pollfd &getPollfdRef();

	static void decrementIdCounter();
	void sendMessage(std::pair<std::string, std::vector<Client> > &msg) const;
	void incrementRetries();
	bool detectedActivity();
	void pushToCommandQueue();

	bool operator==(const Client &rhs);
	bool operator==(const std::string &rhs);

	static std::string receiveData(Client &client);
	
	bool isAuthenticated(void) const;
};

#endif
