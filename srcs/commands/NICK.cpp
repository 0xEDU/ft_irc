#include "ft_irc.hpp"

std::string nick(CommandArgs cArgs)
{
	cArgs.client.setNick(cArgs.msg.args[0]);
	return ("");
}