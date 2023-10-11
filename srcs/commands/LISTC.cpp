#include "ft_irc.hpp"

static std::string channelsListToString(std::vector<std::string> channelsList) {
	if (channelsList.size() == 0)
		return std::string("(none)");

	std::string channelsString;
	for (std::vector<std::string>::iterator it = channelsList.begin(); it != channelsList.end(); it++) {
		channelsString.append(*it);
		if (it + 1 != channelsList.end())
			channelsString.append(", ");
	}
	return channelsString;
}

std::string listc(CommandArgs cArgs)
{
	std::vector<std::string> clientLoggedInChannelsList;

	std::vector<Channel> allChannelsInServer = cArgs.channels;
	for (size_t i = 0; i < allChannelsInServer.size(); i++) {
		std::vector<Client> clientsInChannel = allChannelsInServer[i].getClients();
		for (size_t j = 0; j < clientsInChannel.size(); j++) {
			if (clientsInChannel[j].getNick() == cArgs.client.getNick())
				clientLoggedInChannelsList.push_back(allChannelsInServer[i].getName());
		}
	}

	std::string channelsString = channelsListToString(clientLoggedInChannelsList);
	LOG("User " << cArgs.client.getUser() << " is logged in to the following channels: " << channelsString << std::endl)

	return (std::string("You're currently logged in to the following channels: ").append(channelsString).append("\n"));
}