#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>

const char* SERVER = "localhost";
const int PORT = 6667;
const char* CHANNEL = "#flamengo";
const char* BOT_NICK = "FLABOT";
const char* BOT_PASSWORD = "123";
const char* BOT_REALNAME = "FLAMENBOT";
const char* BOT_USERNAME = "FLAMENBOT";
int   ircSocket = 0;

#define DEBUG(x) std::cout << "[DEBUG] " << x << std::endl;
#define FLAMENGO_ANTHEM1 " :Uma vez Flamengo"
#define FLAMENGO_ANTHEM2 " :Sempre Flamengo"
#define FLAMENGO_ANTHEM3 " :Flamengo sempre eu hei de ser"
#define FLAMENGO_ANTHEM4 " :                             "
#define FLAMENGO_ANTHEM5 " :É meu maior prazer vê-lo brilhar"
#define FLAMENGO_ANTHEM6 " :Seja na terra, seja no mar"
#define FLAMENGO_ANTHEM7 " :Vencer, vencer, vencer"
#define FLAMENGO_ANTHEM8 " :                             "
#define FLAMENGO_ANTHEM9 " :Uma vez Flamengo"
#define FLAMENGO_ANTHEM10 " :Flamengo até morrer"


void send_irc_message(int socket, std::string message) {
    std::string fullMessage = std::string(message) + "\r\n";
    send(socket, fullMessage.c_str(), fullMessage.size(), 0);
}

void toLower(std::string &s) {
    for (size_t i = 0; i < s.size(); i++) {
        s[i] = std::tolower(s[i]);
    }
}

int main() {
    struct sockaddr_in serverAddr;
    struct hostent* server;

    ircSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (ircSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    server = gethostbyname(SERVER);
    if (server == NULL) {
        std::cerr << "Failed to resolve server hostname." << std::endl;
        return 1;
    }
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr = *((struct in_addr*)server->h_addr);
    if (connect(ircSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Failed to connect to the server." << std::endl;
        return 1;
    }
    send_irc_message(ircSocket, "PASS " + std::string(BOT_PASSWORD));
    send_irc_message(ircSocket, "NICK " + std::string(BOT_NICK));
    send_irc_message(ircSocket, "USER " + std::string(BOT_USERNAME) + " 0 0 :" + std::string(BOT_REALNAME));
    send_irc_message(ircSocket, "JOIN " + std::string(CHANNEL));
    while (true) {
        char buffer[4096];
        ssize_t bytes_received = recv(ircSocket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            std::cerr << "Connection closed or error occurred." << std::endl;
            break;
        }
        buffer[bytes_received] = '\0';
        std::string rawData = buffer;
        toLower(rawData);
        if (rawData.find("flamengo não é time") != std::string::npos) {
            send_irc_message(ircSocket, "PRIVMSG " + std::string(CHANNEL) + " :FLAMENGO É SELEÇÃO!!!");
        }
        if (rawData.find("hino do flamengo") != std::string::npos) {
            send_irc_message(ircSocket, "PRIVMSG " + std::string(CHANNEL) + FLAMENGO_ANTHEM1);
            send_irc_message(ircSocket, "PRIVMSG " + std::string(CHANNEL) + FLAMENGO_ANTHEM2);
            send_irc_message(ircSocket, "PRIVMSG " + std::string(CHANNEL) + FLAMENGO_ANTHEM3);
            send_irc_message(ircSocket, "PRIVMSG " + std::string(CHANNEL) + FLAMENGO_ANTHEM4);
            send_irc_message(ircSocket, "PRIVMSG " + std::string(CHANNEL) + FLAMENGO_ANTHEM5);
            send_irc_message(ircSocket, "PRIVMSG " + std::string(CHANNEL) + FLAMENGO_ANTHEM6);
            send_irc_message(ircSocket, "PRIVMSG " + std::string(CHANNEL) + FLAMENGO_ANTHEM7);
            send_irc_message(ircSocket, "PRIVMSG " + std::string(CHANNEL) + FLAMENGO_ANTHEM8);
            send_irc_message(ircSocket, "PRIVMSG " + std::string(CHANNEL) + FLAMENGO_ANTHEM9);
            send_irc_message(ircSocket, "PRIVMSG " + std::string(CHANNEL) + FLAMENGO_ANTHEM10);
        }
    }
    return 0;
}
