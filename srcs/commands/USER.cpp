#include "ft_irc.hpp"

std::string user(CommandArgs cArgs)
{
	if (cArgs.msg.args.size() != 4)
		return ERR_NEEDMOREPARAMS(cArgs.msg.command, "Wrong number of parameters");
	std::string username = cArgs.msg.args[0];
	for (std::size_t i = 0; i < cArgs.clients.size(); i++)
	{
		if (cArgs.clients[i].getUser() == username)
		{
			cArgs.client.setShouldEraseClient(true);
			return (ERR_ALREADYREGISTERED(username));
		}
	}
	cArgs.client.setUser(username);
	cArgs.client.setRealName(cArgs.msg.args[3]);
	if (cArgs.client.getRetries())
		return("");
	if (cArgs.client.isAuthenticated())
		return (RPL_WELCOME(cArgs.client.getNick(), cArgs.client.getUser()));
	return("");
}