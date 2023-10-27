#include "ft_irc.hpp"
#include "replies.hpp"

// Check if the string has unique mode characters
static inline bool containsUniqueModeCharacters(std::string str) {
	std::string modeCharacters = "+-oitkl";
	if (str.size() > modeCharacters.size())
		return false;
	for (size_t i = 0; i < str.length(); ++i) {
		if (modeCharacters.find(str[i]) == std::string::npos
			|| (str[i] == '+' && i != 0)
			|| (str[i] == '-' && i != 0)) {
			return false;
		}
	}
	std::sort(str.begin(), str.end());
	return std::unique(str.begin(), str.end()) == str.end();
}

// Check if the modes in the mode string have a corresponding parameter
static inline bool hasModeCommandsWithParams(std::string modes, std::vector<std::string> modeParams) {
	std::string charactersWithParams;
	modes.find('-') != std::string::npos ? charactersWithParams = "o" : charactersWithParams = "okl";
	size_t paramsCount = 0;
	for (size_t i = 0; i < modes.length(); ++i) {
		if (charactersWithParams.find(modes[i]) != std::string::npos) {
			paramsCount++;
		}
	}
	if (paramsCount != modeParams.size())
		return false;
	return true;
}

static inline bool hasOnlyDigits(const std::string &str) {
    return str.find_first_not_of("0123456789") == std::string::npos;
}

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
		return RPL_CHANNELMODEIS(channelName, modes.first, modes.second);
	}
	if (!channel.isOperator(cArgs.client))
		return ERR_CHANOPRIVSNEEDED(cArgs.client.getUser(), channelName);
	std::string modes = cArgs.msg.args[1];
	std::vector<std::string> modesParams(cArgs.msg.args.begin() + 2, cArgs.msg.args.end());
	if (cArgs.msg.args.size() > 5 || cArgs.msg.args.size() < 2
		|| !containsUniqueModeCharacters(modes)
		|| !hasModeCommandsWithParams(modes, modesParams))
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
				reply.erase(reply.size() - 1);
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
				if (modes.find('-') == std::string::npos) {
					replyParams += modesParams[paramPosition] + " ";
					if (!hasOnlyDigits(modesParams[paramPosition].c_str())
						|| std::atoi(modesParams[paramPosition].c_str()) <= 0)
						return (ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong params"));
					channel.setUserLimit(std::atoi(modesParams[paramPosition++].c_str()));
				} else {
					channel.removeClientLimit();
				}
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
				if (action == false && modes.find('k') != std::string::npos)
					continue;
				replyParams += modesParams[paramPosition] + " ";
				std::vector<Client>::iterator it
					= std::find(channel.getClients().begin(), channel.getClients().end(), modesParams[paramPosition++]);
				if (it == channel.getClients().end())
					return (ERR_NOTONCHANNEL(channelName));
				if (*it == cArgs.client)
					return (ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong params"));
				if (action == true)
					channel.addOperator(*it);
				else if (channel.isOperator(*it))
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
