#include "ft_irc.hpp"

std::string nick(CommandArgs cArgs)
{
	std::string nickname = cArgs.msg.args[0];
	if (nickname == "")
		return (ERR_ERRONEUSNICKNAME(nickname));
	for (std::size_t i = 0; i < cArgs.clients.size(); i++)
	{
		if (cArgs.clients[i].getNick() == nickname)
			return ERR_NICKNAMEINUSE(nickname);
	}
	cArgs.client.setNick(nickname);
	return ("");
}