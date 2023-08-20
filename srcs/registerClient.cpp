#include "ft_irc.hpp"

bool registerClient(Client &client)
{
	char	buff[BUFFER_SIZE];
	
	for (int i = 0; i < 2; i++) {
		std::memset(buff, 0, BUFFER_SIZE);
		if (recv(client.getFd(), buff, BUFFER_SIZE, 0) < 0)
			throw std::runtime_error("Failed to receive message");
	}
	std::string content(buff);
	LOG(content)

	return (false);
}