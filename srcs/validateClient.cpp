#include "ft_irc.hpp"

bool validateClient(Client &client)
{
	std::string data = receiveData(client);
	if (std::count(data.begin(), data.end(), '\n') != 4
		&& std::count(data.begin(), data.end(), '\r') != 4) {
		ERROR("Malformed client message")
		close(client.getFd());
		return (false);
	}
	// while (true) {
	// 	string data = receiveData();
	// 	Message m = parseMsg(data) -> can throw an error;
	//	validate pass
	//  useinfo()
	//	set name, set nick
	// 	if (client.name && client.nick && pass)
	//		break ;
	// }
	
	return (true);
}

// std::istringstream ss(data);
// std::string line;
// while (std::getline(ss, line))
// 	{
// 		std::string token;
// 		std::istringstream ss2(line);
// 		while (ss2 >> token)
// 		{
// 			if (token == "NICK")
// 			{
// 				ss2 >> token;
// 				//ss2 >> token;
// 				client.setNick(token);
// 			}
// 			if (token == "USER")
// 			{
// 				ss2 >> token;
// 				//ss2 >> token;
// 				client.setName(token);
// 			}
// 			if (token == "PASS")
// 			{
// 				ss2 >> token;
// 				if (token != "123")
// 				{
// 					close(client.getFd()); //comentei pra tentar fechar esse fd lá fora;
// 					Client::decrementIdCounter();
// 					ERROR("Wrong password");
// 					return (false);
// 				}
// 			}
// 		}
// 	}