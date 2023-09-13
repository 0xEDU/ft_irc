#include "ft_irc.hpp"

std::string join(CommandArgs cArgs) {
	std::string nicks = "";
	for (size_t i = 0; i < cArgs.clients.size(); i++) {
		nicks = nicks + cArgs.clients[i].getNick() + " ";
	}
	return (":* 332 " + cArgs.client.getNick() + " " + cArgs.msg.args[0] + " :topico\r\n"
	+ ":* 353 " + cArgs.client.getNick() + " = " + cArgs.msg.args[0] + " :@" + nicks + "\r\n"
	+ ":* 366 " + cArgs.client.getNick() + " " + cArgs.msg.args[0] + "\r\n");
}