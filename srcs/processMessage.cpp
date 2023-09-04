#include "ft_irc.hpp"

std::string *processMessage(Message &msg, Client &client)
{
	CommandArgs cArgs = {
		.client = client,
		.msg = msg
		};

	Commands::callFunction(msg.command, cArgs);
	return (Commands::getResponseMessage(msg.command));
}