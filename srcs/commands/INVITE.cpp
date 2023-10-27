#include "ft_irc.hpp"
#include "replies.hpp"
#include <utility>

std::string invite(CommandArgs cArgs)
{
	if (cArgs.msg.args.size() != 2)
		return (ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong params"));
	std::string nickName = cArgs.msg.args[0];
	std::string channelName = cArgs.msg.args[1];
	std::vector<Client>::iterator itClient;
	int foundPosition = -1;

	for (size_t i = 0; i < cArgs.clients.size(); i++) {
		if (cArgs.clients[i].getNick() == nickName) {
			foundPosition = i;
			break ;
		}
	}
	if (foundPosition == -1)
		return ERR_NOSUCHNICK(nickName);
	Client &recipient = cArgs.clients[foundPosition];
	std::vector<Channel>::iterator channelIt = std::find(cArgs.channels.begin(), cArgs.channels.end(), channelName);
	if (channelIt == cArgs.channels.end())
		return ERR_NOSUCHCHANNEL(channelName);
	Channel &channel = *channelIt;
	if (!channel.isClientOnChannel(cArgs.client))
		return ERR_NOTONCHANNEL(channelName);
	if (channel.getIsInviteOnly() && !channel.isOperator(cArgs.client))
		return ERR_CHANOPRIVSNEEDED(cArgs.client.getUser(), channelName);
	if (channel.isClientOnChannel(recipient))
		return ERR_USERONCHANNEL(nickName, channelName);
	std::string recipientReply
		= RPL_INVITEMSG(cArgs.client.getNick(), cArgs.client.getUser(), nickName, channelName);
	std::vector<Client> broadcastList;
	broadcastList.push_back(recipient);
	std::pair<std::string, std::vector<Client> > pair = std::make_pair(recipientReply, broadcastList);
	Client::sendToBroadcastOnly(pair);
	if (channel.getIsInviteOnly())
		recipient.addChannelToInvited(channelName);
	return (RPL_INVITING(cArgs.client.getNick(), nickName, channelName));
}
