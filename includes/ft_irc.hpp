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
#include <fcntl.h>
#include <poll.h>

#include <csignal>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>

#include "classes/Client.hpp"
#include "classes/Message.hpp"
#include "classes/Commands.hpp"
#include "classes/Channel.hpp"
#include "classes/CommandArgs.hpp"
#include "classes/Server.hpp"
#include "classes/Utils.hpp"

#include "replies.hpp"

class Channel;
struct CommandArgs;
class Client;
class Server;

typedef struct sockaddr_in sockAddrIn;
typedef struct sockaddr sockAddr;
typedef struct pollfd pollfd;

#endif
