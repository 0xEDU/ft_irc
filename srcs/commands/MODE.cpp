#include "ft_irc.hpp"

std::string mode(CommandArgs cArgs) {
    std::string channel = cArgs.msg.args[0];
    std::vector<Channel>::iterator it;
    
    it = std::find(cArgs.channels.begin(), cArgs.channels.end(), channel);
    if (it == cArgs.channels.end())
        return ERR_NOSUCHCHANNEL(channel);
    if (!(*it).isClientOnChannel(cArgs.client))
        return ERR_NOTONCHANNEL(channel);
    if (cArgs.msg.args.size() == 1 && cArgs.msg.args[0][0] == '#') {
        std::pair<std::string, std::string> modes = (*it).getModes();
        return RPL_CHANNELMODEIS(channel, modes.first); // broken
    }
    if (!(*it).isOperator(cArgs.client))
        return ERR_CHANOPRIVSNEEDED(cArgs.client.getUser(), channel);
    std::string modes = cArgs.msg.args[1];
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
    return "dale";
}
