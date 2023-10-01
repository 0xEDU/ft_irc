#include "ft_irc.hpp"

std::string user(CommandArgs cArgs)
{
	std::string username = cArgs.msg.args[0];
	for (std::size_t i = 0; i < cArgs.clients.size(); i++)
	{
		if (cArgs.clients[i].getUser() == username)
		{
			cArgs.client.setShouldEraseClient(true);
			return (ERR_ALREADYREGISTERED(username));
		}
	}
	if (cArgs.client.getShouldEraseClient())
		return ("");
	if (cArgs.client.getPass().empty())
	{
		cArgs.client.setShouldEraseClient(true);
		return("");
	}
	cArgs.client.setUser(username);
	cArgs.client.setRealName(cArgs.msg.args[3]);
	if (cArgs.client.getRetries())
		return("");
	return (RPL_WELCOME(cArgs.client.getNick(), cArgs.client.getUser()));
}