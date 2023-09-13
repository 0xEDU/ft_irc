#include "ft_irc.hpp"

std::string quit(CommandArgs cArgs)
{
	cArgs.client.setShouldEraseClient(true);
	return (": Bye bye\r\n");
}