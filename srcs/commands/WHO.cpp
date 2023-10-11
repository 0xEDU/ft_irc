#include "ft_irc.hpp"

std::string who(CommandArgs cArgs) {
    if (cArgs.msg.args.size() < 1)
        return (ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong params"));
    std::string reply;
    std::string channel = cArgs.msg.args[0];
    std::vector<Channel>::iterator it;
    it = std::find(cArgs.channels.begin(), cArgs.channels.end(), channel);
    if (it == cArgs.channels.end())
        return ERR_NOSUCHCHANNEL(channel);

    std::vector<Client> clients = (*it).getClients();
    for (size_t i = 0; i < clients.size(); i++) {
        std::string nick = clients[i].getNick();
        std::string user = clients[i].getUser();
        std::string realName = clients[i].getRealName();
        std::string flags = "H ";
        if ((*it).isOperator(clients[i]))
            flags += "@ ";
        reply += RPL_WHOREPLY(channel, user, nick, flags, realName);
    }
    return reply + RPL_ENDOFWHO(channel);
}
