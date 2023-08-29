#pragma once
#ifndef FT_IRC_HPP
#define FT_IRC_HPP

#define LOG(x) std::cout << x << std::endl;
#define ERROR(x) std::cerr << "Error: " << x << std::endl;
#define CLIENT_LIMIT 1024
#define TIMEOUT 1000
#define BUFFER_SIZE 512

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <poll.h>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include "Client.hpp"
#include "Message.hpp"

class Client;

typedef struct sockaddr_in sockAddrIn;
typedef struct sockaddr sockAddr;
typedef struct pollfd pollfd;

int			getPort(char *input);
int			setupTCP(int port);
void		mainLoop(int sockfd);
std::string receiveData(const Client client);
bool		validateClient(Client &client);
Message 	parseMsg(std::string msg);
#endif
