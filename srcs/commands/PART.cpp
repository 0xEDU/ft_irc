#include "ft_irc.hpp"

std::string part(CommandArgs cArgs)
{
	std::string message;

	// If the client doesn't specify a channel, that is an error
	// Also, verifies if the command passed has a message in it. If it doesn't, the default message is used.
	if (cArgs.msg.args.empty())
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "No channel specified");
	else if (cArgs.msg.args.size() == 2)
		message = cArgs.msg.args[1];
	else
		message = "Leaving";
	
	std::string nick = cArgs.client.getNick();
	std::string user = cArgs.client.getUser();
	std::string returnMessage;
	std::string comma = ",";
	std::vector<std::string> channels = Utils::split(cArgs.msg.args[0], comma);

	for (size_t i = 0; i < channels.size(); i++)
	{
		std::string channelName = channels[i];
		std::vector<Channel>::iterator it;
		it = std::find(cArgs.channels.begin(), cArgs.channels.end(), channelName);

		if (it == cArgs.channels.end())
			return ERR_NOSUCHCHANNEL(channelName);
		if (!(*it).isClientOnChannel(cArgs.client))
			return ERR_NOTONCHANNEL(channelName);
		(*it).removeClient(cArgs.client);//printar os clients dos channels dps daqui
		if ((*it).getClients().empty())
			cArgs.channels.erase(it);//talvez isto não esteja funcionando
		//if (!message.empty())
		returnMessage.append(RPL_PARTMSG(nick, user, channelName, message));
		cArgs.broadcastList = (*it).getClients();//isso aqui vai bugar quando tiver mais de um canal, pq vai sobrescrever
		//else
			//returnMessage.append(RPL_PARTNOMSG(nick, user, channelName));
	}
	return returnMessage;
}
