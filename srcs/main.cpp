#include "ft_irc.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc != 3)
			throw std::logic_error("Usage: ./ircserv <port> <password>");

		// Initialises a function pointer map for each command allowed/defined in the IRC protocol
		Commands::populateMap();

		// Accesses the singleton instance
		Server& server = Server::getInstance();

		// Initialises the attributes of the server (port, password)
		server.setPort(argv[1]);
		server.setPasswd(argv[2]);
		server.setUpTCP();
		server.start();
	}
	catch(const std::exception& e)
	{
		ERROR(e.what())
	}
	
	return (0);
}
