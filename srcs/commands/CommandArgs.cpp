#include "ft_irc.hpp"

CommandArgs::CommandArgs(Client &c, Message m, std::vector<Client> &v)
: client(c), msg(m), clients(v) {}

CommandArgs::~CommandArgs() {}
