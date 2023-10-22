#ifndef FT_IRC_HPP
#define FT_IRC_HPP

#define LOG(x) std::cout << "[INFO] " << x << std::endl;
#define ERROR(x) std::cerr << "[ERROR] IRC Internal error: " << x << std::endl;
#define DEBUG(x) std::cout << "[DEBUG] " << x << std::endl;
#define CLIENT_LIMIT 1024
#define TIMEOUT_MS 1000
#define BUFFER_SIZE 512
#define MAX_PORT_NUMBER 65535 
#define SERVER 0

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
#include <queue>
#include <set>

class Channel;
struct CommandArgs;
class Client;
class Server;

#include "classes/Client.hpp"
#include "classes/RawMessage.hpp"
#include "classes/Commands.hpp"
#include "classes/Channel.hpp"
#include "classes/CommandArgs.hpp"
#include "classes/Server.hpp"
#include "classes/Utils.hpp"

#include "replies.hpp"

typedef struct sockaddr_in sockAddrIn;
typedef struct sockaddr sockAddr;
typedef struct pollfd pollfd;

#endif
