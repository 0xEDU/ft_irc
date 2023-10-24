#include "ft_irc.hpp"

std::string kick(CommandArgs cArgs) {
	// Parameters:
	// <channel>{,<channel>} <user>{,<user>} [<comment>]

	// Numeric Replies:
	// ERR_NEEDMOREPARAMS
	// ERR_CHANOPRIVSNEEDED - operator privileges needed
	// ERR_NOSUCHCHANNEL
	// ERR_NOTONCHANNEL

	if (cArgs.msg.args.size() < 2)
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "Must send at least one channel and one user to kick from channel");

	std::vector<std::string> specifiedChannels = Utils::split(cArgs.msg.args[0], COMMA);
	std::vector<std::string> usersToKick = Utils::split(cArgs.msg.args[1], COMMA);

	if (specifiedChannels.size() == 0)
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "No channels sent in");
	if (usersToKick.size() == 0)
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "No users sent in");
	if (specifiedChannels.size() != usersToKick.size())
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "Asymetric number of channels and users to kick");

	size_t nbOperations = specifiedChannels.size();
	std::string reply;

	for (size_t i = 0; i < nbOperations; i++) {
		// find channel by name
		std::vector<Channel>::iterator channelToKickFrom = std::find(cArgs.channels.begin(), cArgs.channels.end(), specifiedChannels[i]);
		// if channel doesn exist, NOSUCHCHANNEL
		if (channelToKickFrom == cArgs.channels.end()) {
			reply.append(ERR_NOSUCHCHANNEL(specifiedChannels[i]));
			continue ;
		}
		// if requestingClient is not operator, CHANOPRIVSNEEDED
		if (!channelToKickFrom->isOperator(cArgs.client)) {
			reply.append(ERR_CHANOPRIVSNEEDED(cArgs.client.getUser(), channelToKickFrom->getName()));
			continue ;
		}
		// find clientToBeKicked
		std::vector<Client>::iterator clientToBeKicked = std::find(cArgs.clients.begin(), cArgs.clients.end(), usersToKick[i]);
		// if clientToBeKicked doesnt exist or is not on channel, NOTONCHANNEL
		if (clientToBeKicked == cArgs.clients.end() || !channelToKickFrom->isClientOnChannel(usersToKick[i])) {
			reply.append(ERR_USERNOTINCHANNEL(cArgs.client.getUser(), usersToKick[i], specifiedChannels[i]));
			continue ;
		}
		// finally, kicks user out of channel.
		channelToKickFrom->removeClient(*clientToBeKicked);
	}

	return reply;
}
