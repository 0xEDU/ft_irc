#include "ft_irc.hpp"

template<typename T>
struct ChannelOptions {
	bool inviteOnly;
	bool topicRestricted;
	bool hasKey;
	// bool o;
	bool hasLimit;
	std::map<std::string, std::string> channelParameters;

	ChannelOptions() : inviteOnly(false), topicRestricted(false), hasKey(false), hasLimit(false) {};
	ChannelOptions(std::string modeList, std::map<std::string, std::string> modeParams)
		: channelParameters(modeParams)
	{
		bool action;
		for (size_t i = 0; i < modeList.size(); i++) {
			char modeChar = modeList[i];
			if (modeList[i] == '+')
				action = true;
			if (modeList[i] == '-')
				action = false;
			switch (modeChar) {
				case 'i':
					this->inviteOnly = action;
				case 't':
					this->topicRestricted = action;
				case 'k':
					this->hasKey = action;
				case 'l':
					this->hasLimit = action;
				default:
					continue;
			}
		}
	};
	~ChannelOptions() {};
};

// std::map<std::string, std::string>
// generateParametersMap(std::string modes, std::)

std::string mode(CommandArgs cArgs) {
	if (cArgs.msg.args.size() < 1)
		return (ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong params"));
	std::string channelName = cArgs.msg.args[0];
	std::vector<Channel>::iterator it;
	
	it = std::find(cArgs.channels.begin(), cArgs.channels.end(), channelName);
	if (it == cArgs.channels.end())
		return ERR_NOSUCHCHANNEL(channelName);
	Channel &channel = (*it);
	if (!channel.isClientOnChannel(cArgs.client))
		return ERR_NOTONCHANNEL(channelName);
	if (cArgs.msg.args.size() == 1 && (cArgs.msg.args[0][0] == '#' || cArgs.msg.args[0][0] == '&')) {
		std::pair<std::string, std::string> modes = channel.getModes();
		return RPL_CHANNELMODEIS(cArgs.client.getNick(), channelName, modes.first, modes.second);
	}
	if (!channel.isOperator(cArgs.client))
		return ERR_CHANOPRIVSNEEDED(cArgs.client.getUser(), channelName);
	std::string modes = cArgs.msg.args[1];
	std::vector<std::string> modesParams(cArgs.msg.args.begin() + 2, cArgs.msg.args.end());
	DEBUG("MODES: " << modes)
	if (cArgs.msg.args.size() > 5 || cArgs.msg.args.size() < 2
		|| !Utils::containsUniqueModeCharacters(modes)
		|| !Utils::hasModeCommandsWithParams(modes, modesParams))
		return (ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong params"));

	// validateArgs();
	// bool action = true;
	// for (size_t i = 0; i < modes.size(); i++) {
	// 	if (modes[i] == '+')
	// 		action = true;
	// 	if (modes[i] == '-')
	// 		action = false;
	// 	char c = modes[i];
	// 	switch (c) {
	// 		case 'o':
	// 		{
	// 			std::string targetUser;
	// 			LOG(cArgs.msg.args[2])
	// 			if (cArgs.msg.args.size() == 4)
	// 				targetUser = cArgs.msg.args[2];
	// 			if (cArgs.msg.args.size() == 5)
	// 				targetUser = cArgs.msg.args[3];
	// 			if (!channel.isClientOnChannel(targetUser))
	// 				return ERR_NOTONCHANNEL(channelName);
	// 			std::vector<Client>::iterator it = std::find(cArgs.clients.begin(), cArgs.clients.end(), targetUser);
	// 			if (action)
	// 				channel.addOperator(*it);
	// 			else
	// 				channel.removeOperator(*it);
	// 		}
	// 		case 'i':
	// 			LOG("daal")
	// 		case 't':
	// 			LOG("dale")
	// 		case 'l':
	// 			LOG("dale")
	// 		case 'k':
	// 			LOG("dale")
	// 		default:
	// 			continue;
	// 	}
	// }
	return "";
}
