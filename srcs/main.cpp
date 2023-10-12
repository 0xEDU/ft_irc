#include "ft_irc.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc != 3)
			throw std::logic_error("Usage: ./ircserv <port> <password>");
		Server server;

		// Initialises a function pointer map for each command allowed/defined in the IRC protocol
		Commands::populateMap();

		// Initialises the attributes of the server (port, password)
		server.setPort(argv[1]);
		Server::setPasswd(argv[2]);

        server.setUpTCP();
		Server::start();
	}
	catch(const std::exception& e)
	{
		ERROR(e.what())
	}
	
	return (0);
}
