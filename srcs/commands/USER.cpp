#include "ft_irc.hpp"

void user(CommandArgs cArgs)
{
	cArgs.client.setUser(cArgs.msg.args[0]);
	cArgs.client.setRealName(cArgs.msg.args[3]);
}