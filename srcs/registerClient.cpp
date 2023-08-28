#include "ft_irc.hpp"

bool registerClient(Client &client)
{
	char	buff[BUFFER_SIZE];
	
	std::memset(buff, 0, BUFFER_SIZE);
	std::string content;
	while (count(content.begin(), content.end(), '\n') < 4)
	{
		if (recv(client.getFd(), buff, BUFFER_SIZE, 0) < 0)
			throw std::runtime_error("Failed to receive message");
		content += buff;
	}
	//parse content
	std::cout << "Content = " << content << std::endl;
	for (std::string::iterator it = content.begin(); it != content.end(); it++) {
		std::cout << static_cast<int>(*it) << " ";
	}
	std::cout << std::endl;
	exit(0);
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
				//ss2 >> token;
				client.setNick(token);
			}
			if (token == "USER")
			{
				ss2 >> token;
				//ss2 >> token;
				client.setName(token);
			}
			if (token == "PASS")
			{
				ss2 >> token;
				if (token != "123")
				{
					close(client.getFd()); //comentei pra tentar fechar esse fd lá fora;
					Client::decrementIdCounter();
					ERROR("Wrong password");
					return (false);
				}
			}
		}
	}
	return (true);
}