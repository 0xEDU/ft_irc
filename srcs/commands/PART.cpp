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
		if (!it->isClientOnChannel(cArgs.client))
			return ERR_NOTONCHANNEL(channelName);
		cArgs.broadcastList = it->getClients();//isso aqui vai bugar quando tiver mais de um canal, pq vai sobrescrever
		it->removeClient(cArgs.client);
		if (it->getClients().empty())
			cArgs.channels.erase(it);
		if (!message.empty())
			returnMessage.append(RPL_PARTMSG(user, nick, channelName, message));
			//chamar o send pra broadcast list
			//limpar a broadcast list
		else
			returnMessage.append(RPL_PARTNOMSG(user, nick, channelName));
			//chamar o send pra broadcast list
			//limpar a broadcast list
	}
	return returnMessage;
}
