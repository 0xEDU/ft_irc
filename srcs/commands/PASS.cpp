#include "ft_irc.hpp"

std::string pass(CommandArgs cArgs)
{
	if (cArgs.msg.args.size() != 1)
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong number of parameters");
	if (!cArgs.client.getPass().empty())
		return ERR_ALREADYREGISTERED(cArgs.client.getUser());
	cArgs.client.setPass(cArgs.msg.args[0]);
	if (cArgs.client.getPass() != Server::getPasswd())
	{
		cArgs.client.setShouldEraseClient(true);
		return (ERR_PASSWDMISMATCH());
	}
	if (cArgs.client.isAuthenticated())
		return (RPL_WELCOME(cArgs.client.getNick(), cArgs.client.getUser()));
	return ("");
}