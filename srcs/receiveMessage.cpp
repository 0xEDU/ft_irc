#include "ft_irc.hpp"

Message receiveMessage(const Client client)
{
	while(true)
	{
		char	buff[BUFFER_SIZE];
		
		std::memset(buff, 0, BUFFER_SIZE);
		if (recv(client.getFd(), buff, BUFFER_SIZE, 0) < 0)
			throw std::runtime_error("Failed to receive message");
	}
	
}