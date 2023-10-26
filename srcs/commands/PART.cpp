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
		std::vector<Client> broadcastList;
		std::string reply;
		std::pair<std::string, std::vector<Client> > broadcastPair; //compor um par por iteração no for causa algum problema?

		if (it == cArgs.channels.end())
			return ERR_NOSUCHCHANNEL(channelName);
		if (!it->isClientOnChannel(cArgs.client))
			return ERR_NOTONCHANNEL(channelName);
		it->removeClient(cArgs.client);
		broadcastList = it->getClients();
		if (it->getClients().empty())
			cArgs.channels.erase(it);
		if (!message.empty())
		{
			reply = RPL_PARTMSG(user, nick, channelName, message);
			broadcastPair = std::make_pair(reply, broadcastList);
			Client::sendToBroadcastOnly(broadcastPair);
			broadcastList.clear();
			returnMessage.append(reply);
		}
		else
		{
			reply = RPL_PARTNOMSG(user, nick, channelName);
			broadcastPair = std::make_pair(reply, broadcastList);//chamar o send pra broadcast list
			Client::sendToBroadcastOnly(broadcastPair);
			broadcastList.clear(); //limpar a broadcast list
			returnMessage.append(RPL_PARTNOMSG(user, nick, channelName));
		}
	}
	return returnMessage;
}
