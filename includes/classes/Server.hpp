#pragma once
#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"

class Server
{
	private:

	static int _port;
	static int _serverSocketDescriptor;
	static std::string _passwd;

	// Prevent instantiation of class
	Server();
	~Server();
	// Prevent copying
	Server(const Server&);
	Server& operator=(const Server&);

	// Private methods
	// void bindSocket();
	// void createSocket();
	// void configureAddress();
	// void listenForClients();
	static void sigHandler(int);

	public:
	static Server& getInstance();

	void setUpTCP() const;
	static void start();

	void setPort(char *input);
	static std::string getPasswd();
	static void setPasswd(char *passwd);
};

#endif