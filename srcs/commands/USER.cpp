#include "ft_irc.hpp"

std::string user(CommandArgs cArgs)
{
	std::string username = cArgs.msg.args[0];
	for (std::size_t i = 0; i < cArgs.clients.size(); i++)
	{
		if (cArgs.clients[i].getUser() == username)
		{
			cArgs.client.setShouldEraseClient(1);
			return (ERR_ALREADYREGISTERED(username));
		}
	}
	cArgs.client.setUser(username);
	cArgs.client.setRealName(cArgs.msg.args[3]);
	if (cArgs.client.getShouldEraseClient())
		return ("");
	return (RPL_WELCOME(cArgs.client.getNick(), cArgs.client.getUser()));
}