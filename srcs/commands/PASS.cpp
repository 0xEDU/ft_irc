#include "ft_irc.hpp"

std::string pass(CommandArgs cArgs)
{
	std::string pass = cArgs.msg.args[0];
	if (pass != Server::getPasswd())
		return (ERR_PASSWDMISMATCH);
	return ("");
}