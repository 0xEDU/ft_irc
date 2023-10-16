#include "ft_irc.hpp"
#include "replies.hpp"

std::string topic(CommandArgs cArgs) {
	if (cArgs.msg.args.size() < 1 || cArgs.msg.args.size() > 3)
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong number of parameters for TOPIC");
	std::string clientNick = cArgs.client.getNick();
	std::string clientUser = cArgs.client.getUser();
	std::string channelName = cArgs.msg.args[0];
	std::vector<Channel>::iterator it = std::find(cArgs.channels.begin(), cArgs.channels.end(), channelName);
	if (it == cArgs.channels.end())
		return ERR_NOTONCHANNEL(channelName);
	Channel &channel = (*it);
	if (cArgs.msg.args.size() == 1) {
		std::string currentTopic = channel.getTopic();
		if (currentTopic.empty())
			return RPL_NOTOPIC(clientNick, channelName);
		return RPL_TOPIC(clientNick, channelName, currentTopic);
	}
	if (!channel.isOperator(cArgs.client) && !channel.isTopicOPOnly())
		return ERR_CHANOPRIVSNEEDED(cArgs.client.getUser(), channelName);
	std::string topicString = cArgs.msg.args[1];
	channel.setTopic(topicString);
	for (size_t i = 0; i < channel.getClients().size(); i++)
		cArgs.broadcastList.push_back(channel.getClients()[i]);
	return PRIVMSG_BROADCAST(clientNick, clientUser, channelName, topicString);
}
