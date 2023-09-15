#include "ft_irc.hpp"

std::string processMessage(Message &msg, Client &client, std::vector<Client> &clients, std::vector<Channel> &channels)
{
	CommandArgs cArgs = CommandArgs(client, msg, clients, channels);

	return (Commands::callFunction(msg.command, cArgs));
}
