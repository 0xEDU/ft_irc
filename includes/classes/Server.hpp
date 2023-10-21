#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"

class Server
{
	private:

	static int			_serverPort;
	static int			_serverSocketDescriptor;
	static pollfd		*_serverPollfd;
	static sockaddr_in	_serverAddr;
	static std::string	_serverPassword;

	static std::vector<pollfd> _connectionsPollfds;
	static std::vector<Client> _clients;
	static std::vector<Channel> _channels;

	// Prevent instantiation of class
	Server();
	~Server();
	// Prevent copying
	Server(const Server&);
	Server& operator=(const Server&);

	// Private methods
	static void bindSocketToAddress();
	static void createSocket();
	static void configureAddress();
	static void listenForClients();
	static void sigHandler(int);

	static void pollActiveConnections(void);
	static void processClientsActivity(void);
	static void acceptNewClients(void);

	public:

	static Server& getInstance();

	static void setUpTCP();
	static void start();

	void setPort(char *input);
	static std::string getPasswd();
	static void setPasswd(char *passwd);
};

#endif