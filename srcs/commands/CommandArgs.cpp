#include "ft_irc.hpp"

CommandArgs::CommandArgs(Client &client, const Message& msg, std::vector<Client> &clients, std::vector<Channel> &channels)
: client(client), msg(msg), clients(clients), channels(channels) {}

CommandArgs::~CommandArgs() {}
