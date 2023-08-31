#include "ft_irc.hpp"

void processMessage(Message &msg, Client &client)
{
	CommandArgs cArgs = {
		.client = client,
		.msg = msg
		};

	Commands::callFunction(msg.command, cArgs);
}