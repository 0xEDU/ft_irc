#pragma once
#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"

class Server
{
	private:

	static int			_port;
	static int			_serverSocketDescriptor;
	static sockaddr_in	_serverAddr;
	static std::string	_passwd;

	static std::vector<pollfd> _connections;
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
	static void checkForNewConnections(void);

	public:

	static Server& getInstance();

	static void setUpTCP();
	static void start();

	void setPort(char *input);
	static std::string getPasswd();
	static void setPasswd(char *passwd);
};

#endif