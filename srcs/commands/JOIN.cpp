#include "ft_irc.hpp"

std::string join(CommandArgs cArgs) {
	std::string nicks = "";
	for (size_t i = 0; i < cArgs.clients.size(); i++) {
		nicks = nicks + cArgs.clients[i].getNick() + " ";
	}
	if (cArgs.msg.args[0][0] != '#')
		return (" : ERROR");
	std::vector<Channel>::iterator it;
	it = find (cArgs.channels.begin(), cArgs.channels.end(), cArgs.msg.args[0]);
	if (it != cArgs.channels.end())
		(*it).addClient(cArgs.client);
	else
	{
		Channel newChannel(cArgs.msg.args[0]);
		cArgs.channels.push_back(newChannel);
		newChannel.addClient(cArgs.client);
	}
	return (":* 332 " + cArgs.client.getNick() + " " + cArgs.msg.args[0] + " :topico\r\n"
	+ ":* 353 " + cArgs.client.getNick() + " = " + cArgs.msg.args[0] + " :@" + nicks + "\r\n"
	+ ":* 366 " + cArgs.client.getNick() + " " + cArgs.msg.args[0] + "\r\n");
}