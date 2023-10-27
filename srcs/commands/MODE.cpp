#include "ft_irc.hpp"
#include "replies.hpp"

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
		return RPL_CHANNELMODEIS(channelName, modes.first, modes.second); // Test for this later
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
	bool action = true;
	std::string reply = RPL_MODEBASE(cArgs.client.getNick(), cArgs.client.getUser(), channelName);
	reply += '+';
	std::string replyParams;
	size_t paramPosition = 0;
	for (size_t i = 0; i < modes.size(); i++) {
		char modeChar = modes[i];
		switch (modeChar) {
			case '-': {
				action = false;
				reply.erase(reply.size() - 1); // IM SORRY FOR THIS
				reply += '-';
				continue;
			}
			case 'i': {
				channel.setIsInviteOnly(action);
				reply += 'i';
				continue;
			}
			case 't': {
				channel.setTopicRestricted(action);
				reply += 't';
				continue;
			}
			case 'l': {
				if (modes.find('-') == std::string::npos)
					replyParams += modesParams[paramPosition] + " ";
				if (action == true)
					channel.setUserLimit(static_cast<int>(std::atoi(modesParams[paramPosition++].c_str())));
				else
					channel.removeClientLimit();
				reply += 'l';
				continue;
			}
			case 'k': {
				if (modes.find('-') == std::string::npos)
					replyParams += modesParams[paramPosition] + " ";
				if (action == true)
					channel.setKey(modesParams[paramPosition++]);
				else
					channel.removeKey();
				reply += 'k';
				continue;
			}
			case 'o': {

				replyParams += modesParams[paramPosition] + " ";
				DEBUG(modesParams[paramPosition])
				std::vector<Client>::iterator it = std::find(channel.getClients().begin(), channel.getClients().end(), modesParams[paramPosition++]);
				if (it == channel.getClients().end())
					return (ERR_NOTONCHANNEL(channelName));
				if (*it == cArgs.client)
					return (ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong params"));
				if (action == true)
					channel.addOperator(*it);
				else
					channel.removeOperator(*it);
				reply += 'o';
				continue;
			}
			default:
				continue;
		}
	}
	reply += " " + replyParams;
	reply += CRLF;
	cArgs.broadcastList = channel.getClients();
	return reply;
}
