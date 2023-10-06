#include "ft_irc.hpp"

std::string mode(CommandArgs cArgs) {
    std::string channelName = cArgs.msg.args[0];
    std::vector<Channel>::iterator it;
    
    it = std::find(cArgs.channels.begin(), cArgs.channels.end(), channelName);
    if (it == cArgs.channels.end())
        return ERR_NOSUCHCHANNEL(channelName);
    Channel &channel = (*it);
    if (!channel.isClientOnChannel(cArgs.client))
        return ERR_NOTONCHANNEL(channelName);
    if (cArgs.msg.args.size() == 1 && cArgs.msg.args[0][0] == '#') {
        std::pair<std::string, std::string> modes = channel.getModes();
        return RPL_CHANNELMODEIS(channelName.substr(1, channelName.size() - 1), modes.first, modes.second);
    }
    if (!channel.isOperator(cArgs.client))
        return ERR_CHANOPRIVSNEEDED(cArgs.client.getUser(), channelName);
    std::string modes = cArgs.msg.args[1];
    if (cArgs.msg.args.size() > 4 || cArgs.msg.args.size() < 2)
        return (ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong params"));
    bool action = true;
    for (size_t i = 0; i < modes.size(); i++) {
        if (modes[i] == '+')
            action = true;
        if (modes[i] == '-')
            action = false;
        char c = modes[i];
        switch (c) {
            case 'o':
            {
                std::string targetUser;
                LOG(cArgs.msg.args[2])
                if (cArgs.msg.args.size() == 4)
                    targetUser = cArgs.msg.args[2];
                if (cArgs.msg.args.size() == 5)
                    targetUser = cArgs.msg.args[3];
                if (!channel.isClientOnChannel(targetUser))
                    return ERR_NOTONCHANNEL(channelName);
                std::vector<Client>::iterator it = std::find(cArgs.clients.begin(), cArgs.clients.end(), targetUser);
                if (action)
                    channel.addOperator(*it);
                else
                    channel.removeOperator(*it);
            }
            case 'i':
                LOG('daal')
            case 't':
                LOG('dale')
            case 'l':
                LOG('dale')
            case 'k':
                LOG('dale')
            default:
                continue;
        }
    }
    return "";
}
