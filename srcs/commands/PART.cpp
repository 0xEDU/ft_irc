#include "ft_irc.hpp"

std::string part(CommandArgs cArgs) {
    std::string nick = cArgs.client.getNick();
    std::string user = cArgs.client.getUser();
    std::string message = cArgs.msg.args.back();
    std::string returnMessage;

    for (size_t i = 0; i < cArgs.msg.args.size() - 1; i++) {
        std::vector<Channel>::iterator it;
        std::string channel = cArgs.msg.args[i];
        it = std::find(cArgs.channels.begin(), cArgs.channels.end(), channel);
        if (it == cArgs.channels.end())
            return channel + ":No such channel\r\n"; // Add reply
        (*it).disconnectClient(cArgs.client);
        if ((*it).getClients().empty()) {
            cArgs.channels.erase(it);
        }
        returnMessage.append(RPL_PART(nick, user, channel, message));
    }
    return returnMessage;
}
