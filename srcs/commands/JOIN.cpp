#include "classes/Utils.hpp"

std::string join(CommandArgs cArgs) {
	std::string nick = cArgs.client.getNick();
	std::string user = cArgs.client.getUser();
	std::vector<std::string> channels = Utils::split(cArgs.msg.args[0], COMMA);
	std::vector<std::string> keys;
	if (cArgs.msg.args.size() > 1)
		keys = Utils::split(cArgs.msg.args[1], COMMA);
	std::string reply;

	if (keys.size() != channels.size() && !keys.empty())
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "Nope");
	if (channels[0] == "0") // This might cause some trouble if user sends JOIN 0,#anotherchannel. Further investigation needed
	{
		std::string argument;
		for (size_t i = 0; i < cArgs.channels.size(); i++)
			argument += cArgs.channels[i].getName() + ",";
		argument.erase(argument.size() - 1);
		cArgs.msg.args[0] = argument;
		return part(cArgs);
	}
	// This should loop through all the channels and create them/add user to them or fail. Further testing is required for treating exceptions
	for (size_t i = 0; i < channels.size(); i++) {
		std::string channelUsers;
		std::string channelName = channels[i];
		std::string channelKey;
		if (!keys.empty())
			channelKey = keys[i];
		std::string nicks;
		std::string topicMessage;
		for (size_t i = 0; i < cArgs.clients.size(); i++) {
			nicks += nick + " ";
		}
		if (channelName[0] != '#' && channelName[0] != '&') {
			reply += ERR_NOSUCHCHANNEL(channelName);
			continue;
		}
		std::vector<Channel>::iterator it;
		it = find (cArgs.channels.begin(), cArgs.channels.end(), channelName);
		Channel &channel = *it;
		if (it != cArgs.channels.end()) {
			if (channel.isClientOnChannel(cArgs.client))
				continue ;
			if ((channel.getKey() != "") && (channel.getKey() != channelKey)) {
				reply += ERR_BADCHANNELKEY(cArgs.client.getUser(), channelName);
				continue ;
			}
			if (channel.getClients().size() == channel.getUserLimit()) {
				reply += ERR_CHANNELISFULL(channelName);
				continue ;
			}
			channel.addClient(cArgs.client);
			channelUsers = channel.getChannelUsers();
			for (size_t i = 0; i < channel.getClients().size(); i++)
				cArgs.broadcastList.push_back(channel.getClients()[i]);
			topicMessage = channel.getTopic();
		}
		else
		{
			Channel newChannel(channelName);
			newChannel.addClient(cArgs.client);
			newChannel.addOperator(cArgs.client);
			if (!channelKey.empty())
				newChannel.setKey(channelKey);
			channelUsers = newChannel.getChannelUsers();
			cArgs.channels.push_back(newChannel);
		}
		reply += (JOIN(user, channelName)
		+ (topicMessage.empty() ? "" : RPL_TOPIC(nick, channelName, topicMessage)) // If the channel doesn't have a topic, don't append RPL_TOPIC to final reply
		+ RPL_NAMREPLY(nick, channelName, channelUsers)
		+ RPL_ENDOFNAMES(nick, channelName));
	}
	return reply;
}
