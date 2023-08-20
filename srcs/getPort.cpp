#include "ft_irc.hpp"

int	getPort(char *input)
{
	int port = std::atoi(input);
	
	if (port < 0 || port > 65535)
		throw std::logic_error("Invalid port number");
	return (port);
}