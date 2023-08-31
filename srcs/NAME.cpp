#include "ft_irc.hpp"

void name(CommandArgs cArgs)
{
	cArgs.client.setName(cArgs.msg.args[0]);
}