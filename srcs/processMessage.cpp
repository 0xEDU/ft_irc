#include "ft_irc.hpp"

std::string processMessage(Message &msg, Client &client, std::vector<Client> &clients)
{
	CommandArgs cArgs = {
		.client = client,
		.msg = msg,
		.clients = clients
	};

	return (Commands::callFunction(msg.command, cArgs));
}
