#include "ft_irc.hpp"

std::string nick(CommandArgs cArgs)
{
	if (cArgs.msg.args.size() < 1)
		return ERR_NONICKNAMEGIVEN();
	std::string nickname = cArgs.msg.args[0];
	if (nickname.empty())
	{
		cArgs.client.incrementRetries();
		return (ERR_ERRONEUSNICKNAME(nickname));
	}
	for (std::size_t i = 0; i < cArgs.clients.size(); i++)
	{
		if (cArgs.clients[i].getNick() == nickname)
		{
			cArgs.client.incrementRetries();
			return ERR_NICKNAMEINUSE(nickname);
		}
	}
	cArgs.client.setNick(nickname);
	if (cArgs.client.isAuthenticated())
		return (RPL_WELCOME(cArgs.client.getNick(), cArgs.client.getUser()));
	return ("");
}