#include "ft_irc.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc != 3)
			throw std::logic_error("Usage: ./ircserv <port> <password>");
		Server server;
		Commands::populateMap();
		server.setPort(argv[1]);
		Server::setPasswd(argv[2]);
        server.setupTCP();
		Server::mainLoop();
	}
	catch(const std::exception& e)
	{
		ERROR(e.what())
	}
	
	return (0);
}
