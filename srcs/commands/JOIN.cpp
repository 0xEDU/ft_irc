#include "classes/Utils.hpp"

std::string join(CommandArgs cArgs) {
	std::string nick = cArgs.client.getNick();
	std::string user = cArgs.client.getUser();
	std::vector<std::string> channels = Utils::split(cArgs.msg.args[0], ",");
	std::string reply;

	if (channels[0] == "0") // This might cause some trouble if user sends JOIN 0 #anotherchannel. Further investigation needed
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
		std::string channel = channels[i];
		std::string nicks;
		std::string topicMessage;
		for (size_t i = 0; i < cArgs.clients.size(); i++) {
			nicks += nick + " ";
		}
		if (channel[0] != '#') {
			reply += ERR_NOSUCHCHANNEL(channel);
			continue;
		}
		std::vector<Channel>::iterator it;
		it = find (cArgs.channels.begin(), cArgs.channels.end(), channel);
		if (it != cArgs.channels.end()) {
			(*it).addClient(cArgs.client);
			channelUsers = (*it).getChannelUsers();
			for (size_t i = 0; i < (*it).getClients().size(); i++)
				cArgs.broadcastList.push_back((*it).getClients()[i]);
			topicMessage = (*it).getTopic();
		}
		else
		{
			Channel newChannel(channel);
			newChannel.addClient(cArgs.client);
			newChannel.addOperator(cArgs.client);
			channelUsers = newChannel.getChannelUsers();
			cArgs.channels.push_back(newChannel);
		}
		reply += (JOIN(user, channel)
		+ (topicMessage.empty() ? "" : RPL_TOPIC(nick, channel, topicMessage)) // If the channel doesn't have a topic, don't append RPL_TOPIC to final reply
		+ RPL_NAMREPLY(nick, channel, channelUsers)
		+ RPL_ENDOFNAMES(nick, channel));
	}
	return reply;
}
