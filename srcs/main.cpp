#include "ft_irc.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc != 3)
			throw std::logic_error("Usage: ./ircserv <port> <password>");
		Commands::populateMap();
		int port = getPort(argv[1]);
		int socket_fd = setupTCP(port);
		mainLoop(socket_fd);
	}
	catch(const std::exception& e)
	{
		ERROR(e.what());
	}
	
	return (0);
}
