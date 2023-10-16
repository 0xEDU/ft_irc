#include "ft_irc.hpp"

CommandArgs::CommandArgs(Client &client, RawMessage &msg, std::vector<Client> &clients, std::vector<Channel> &channels,
						 std::vector<Client> &broadcastList)
: client(client), msg(msg), clients(clients), broadcastList(broadcastList), channels(channels) {}

CommandArgs::~CommandArgs() {}
