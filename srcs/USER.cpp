#include "ft_irc.hpp"

void user(CommandArgs cArgs)
{
	cArgs.client.setUser(cArgs.msg.args[0]);
}