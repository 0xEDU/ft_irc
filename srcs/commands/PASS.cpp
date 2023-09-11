#include "ft_irc.hpp"

std::string pass(CommandArgs cArgs)
{
	std::string pass = cArgs.msg.args[0];
	if (pass != Server::getPasswd())
	{
		cArgs.client.setShouldEraseClient(1);
		return (ERR_PASSWDMISMATCH);
	}
	return ("");
}