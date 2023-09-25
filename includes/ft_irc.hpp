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
#include <utility>

#include "Client.hpp"
#include "Message.hpp"
#include "Commands.hpp"
#include "Channel.hpp"
#include "CommandArgs.hpp"
#include "Server.hpp"

#include "replies.hpp"

class Channel;
struct CommandArgs;
class Client;
class Server;

typedef struct sockaddr_in sockAddrIn;
typedef struct sockaddr sockAddr;
typedef struct pollfd pollfd;

std::string					receiveData(Client &client);
Message 					parseMsg(std::string msg);
std::vector<std::string> split(const std::string &s, const std::string& delimiter = " ");
std::pair<std::string, std::vector<Client> >
processMessage(Message &msg, Client &client, std::vector<Client> &clients, std::vector<Channel> &channels);

#endif
