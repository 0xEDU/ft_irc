#include "ft_irc.hpp"

std::pair<std::string, std::vector<Client> >
processMessage(Message &msg, Client &client, std::vector<Client> &clients, std::vector<Channel> &channels)
{
    std::vector<Client> broadcastList;
	CommandArgs cArgs = CommandArgs(client, msg, clients, channels, broadcastList);

	return (std::make_pair(Commands::callFunction(msg.command, cArgs), broadcastList));
}
