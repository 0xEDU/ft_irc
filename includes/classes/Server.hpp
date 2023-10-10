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

	static void sigHandler(int);

	public:

	Server();
	~Server();

	void setupTCP() const;
	static void start();

	void setPort(char *input);
	static std::string getPasswd();
	static void setPasswd(char *passwd);
};

#endif