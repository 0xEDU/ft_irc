#include "ft_irc.hpp"

void nick(CommandArgs cArgs)
{
	cArgs.client.setNick(cArgs.msg.args[0]);
}