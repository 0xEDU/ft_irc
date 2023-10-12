#include "ft_irc.hpp"

std::string join(CommandArgs cArgs) {
	std::string nick = cArgs.client.getNick();
	std::string user = cArgs.client.getUser();
	std::string channel = cArgs.msg.args[0];
	std::string channelUsers;

	std::string nicks;
	for (size_t i = 0; i < cArgs.clients.size(); i++) {
		nicks += nick + " ";
	}
	if (channel == "0")
	{
		std::string argument;
		for (size_t i = 0; i < cArgs.channels.size(); i++)
			argument += cArgs.channels[i].getName() + ",";
		argument.erase(argument.size() - 1);
		cArgs.msg.args[0] = argument;
		return part(cArgs);
	}
	if (channel[0] != '#')
		return (ERR_NOSUCHCHANNEL(channel));
	std::vector<Channel>::iterator it;
	it = find (cArgs.channels.begin(), cArgs.channels.end(), channel);
	if (it != cArgs.channels.end()) {
		(*it).addClient(cArgs.client);
		channelUsers = (*it).getChannelUsers();
		for (size_t i = 0; i < (*it).getClients().size(); i++)
			cArgs.broadcastList.push_back((*it).getClients()[i]);
	}
	else
	{
		Channel newChannel(channel);
		newChannel.addClient(cArgs.client);
		newChannel.addOperator(cArgs.client);
		channelUsers = newChannel.getChannelUsers();
		cArgs.channels.push_back(newChannel);
	}
	return (JOIN(user,channel)
	+ RPL_TOPIC(nick, channel, "topic")
	+ RPL_NAMREPLY(nick, channel, channelUsers)
	+ RPL_ENDOFNAMES(nick, channel));
}