#include "ft_irc.hpp"

std::string join(CommandArgs cArgs) {
	std::string nick = cArgs.client.getNick();
	std::string user = cArgs.client.getUser();
	std::string channel = cArgs.msg.args[0];
	std::string channelUsers = " gui edu rods";

	std::string nicks;
	for (size_t i = 0; i < cArgs.clients.size(); i++) {
		nicks += nick + " ";
	}
	if (channel[0] != '#')
		return (" : ERROR"); // Reply
	std::vector<Channel>::iterator it;
	it = find (cArgs.channels.begin(), cArgs.channels.end(), channel);
	if (it != cArgs.channels.end())
		(*it).addClient(cArgs.client);
	else
	{
		Channel newChannel(channel);
		cArgs.channels.push_back(newChannel);
		newChannel.addClient(cArgs.client);
	}
	return (JOIN(user,channel)
	+ RPL_TOPIC(nick, channel, "topic")
	+ RPL_NAMREPLY(nick, channel, "@" + user + channelUsers)
	+ RPL_ENDOFNAMES(nick, channel));
}