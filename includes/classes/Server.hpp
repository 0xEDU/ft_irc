#pragma once
#ifndef SERVER_HPP
#define SERVER_HPP

#include "ft_irc.hpp"

class Server
{
	private:

	int _port;
	static int _serverFd;
	static std::string _passwd;

	// void bindSocket();
	// void createSocket();
	// void configureAddress();
	// void listenForClients();
	static void sigHandler(int);

	public:

	Server();
	~Server();

	void setUpTCP() const;
	static void start();

	void setPort(char *input);
	static std::string getPasswd();
	static void setPasswd(char *passwd);
};

#endif