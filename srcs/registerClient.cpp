#include "ft_irc.hpp"

bool registerClient(Client &client)
{
	char	buff[BUFFER_SIZE];
	
	std::memset(buff, 0, BUFFER_SIZE);
	if (recv(client.getFd(), buff, BUFFER_SIZE, 0) < 0)
		throw std::runtime_error("Failed to receive message");
	std::string content(buff);
	//parse content
	std::istringstream ss(content);
	std::string line;
	while (std::getline(ss, line))
	{
		std::string token;
		std::istringstream ss2(line);
		while (ss2 >> token)
		{
			if (token == "NICK")
			{
				ss2 >> token;
				ss2 >> token;
				client.setNick(token);
			}
			if (token == "USER")
			{
				ss2 >> token;
				ss2 >> token;
				client.setName(token);
			}
			if (token == "PASS")
			{
				ss2 >> token;
				if (token != "123")
				{
					close(client.getFd());
					ERROR("Wrong password");
					return (false);
				}
			}
		}
	}
	return (true);
}