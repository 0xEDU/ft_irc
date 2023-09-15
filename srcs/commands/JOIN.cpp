#include "ft_irc.hpp"

std::string join(CommandArgs cArgs) {
	std::string nick = cArgs.client.getNick();
	std::string user = cArgs.client.getUser();
	std::string channel = cArgs.msg.args[0];
	std::string channelUsers = " gui edu rods";

	return (JOIN(user,channel)
	+ RPL_TOPIC(nick, channel, "topic")
	+ RPL_NAMREPLY(nick, channel, "@" + user + channelUsers)
	+ RPL_ENDOFNAMES(nick, channel));
}