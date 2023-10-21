#include "ft_irc.hpp"

std::string part(CommandArgs cArgs) {
	std::string message;
	if (cArgs.msg.args.empty())
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "Not enough parameters");
	if (cArgs.msg.args.size() == 2)
		message = cArgs.msg.args[1];
	std::string nick = cArgs.client.getNick();
	std::string user = cArgs.client.getUser();
	std::string returnMessage;
	std::string comma = ",";
	std::vector<std::string> channels = Utils::split(cArgs.msg.args[0], comma);

	for (size_t i = 0; i < channels.size(); i++) {
		std::string channel = channels[i];
		std::vector<Channel>::iterator it;
		it = std::find(cArgs.channels.begin(), cArgs.channels.end(), channel);
		if (it == cArgs.channels.end())
			return ERR_NOSUCHCHANNEL(channel);
		if (!(*it).isClientOnChannel(cArgs.client))
			return ERR_NOTONCHANNEL(channel);
		(*it).disconnectClient(cArgs.client);
		if ((*it).getClients().empty())
			cArgs.channels.erase(it);
		if (!message.empty())
			returnMessage.append(RPL_PARTMSG(nick, user, channel, message));
		else
			returnMessage.append(RPL_PARTNOMSG(nick, user, channel));
	}
	return returnMessage;
}
