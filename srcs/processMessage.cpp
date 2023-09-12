#include "ft_irc.hpp"

std::string processMessage(Message &msg, Client &client, std::vector<Client> &clients)
{
	CommandArgs cArgs = CommandArgs(client, msg, clients);

	return (Commands::callFunction(msg.command, cArgs));
}
