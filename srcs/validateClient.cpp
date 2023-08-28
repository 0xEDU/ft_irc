#include "ft_irc.hpp"

bool validateClient(Client &client)
{
	std::string msg = receiveMessage(client);
	if (std::count(msg.begin(), msg.end(), '\n') != 4
		&& std::count(msg.begin(), msg.end(), '\r') != 4) {
		ERROR("Malformed client message")
		close(client.getFd());
		return (false);
	}
	std::istringstream ss(msg);
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