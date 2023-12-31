#include "ft_irc.hpp"

std::string privmsg(CommandArgs cArgs) {
	std::string nick = cArgs.client.getNick();
	std::string user = cArgs.client.getUser();
	if (cArgs.msg.args.size() < 1)
		return ERR_NORECIPIENT(user);
	if (cArgs.msg.args.size() < 2)
		return ERR_NOTEXTTOSEND(user);
	std::string recipient = cArgs.msg.args[0];
	std::string message = cArgs.msg.args[1];

	if (recipient[0] == '#' || recipient[0] == '&') {
		std::vector<Channel>::iterator itChannel;
		std::vector<Client>::iterator itClient;
		itChannel = std::find(cArgs.channels.begin(), cArgs.channels.end(), recipient);
		if (itChannel == cArgs.channels.end())
			return (ERR_NOTONCHANNEL((recipient)));
		if (itChannel->getClients().size() == 1)
			return "";
		cArgs.broadcastList = itChannel->getClients();
		itClient = std::find(cArgs.broadcastList.begin(), cArgs.broadcastList.end(), cArgs.client);
		cArgs.broadcastList.erase(itClient); // Remove the client sending the message, so it doesn't send to itself :)
	} else {
		std::vector<Client>::iterator itClient;
		itClient = std::find(cArgs.clients.begin(), cArgs.clients.end(), recipient);
		if (itClient == cArgs.clients.end())
			return ERR_NOSUCHNICK(recipient);
		cArgs.broadcastList.push_back((*itClient));

	}
	return RPL_PRIVMSG(user, recipient, message);
}
