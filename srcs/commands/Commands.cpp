#include "ft_irc.hpp"

std::map<std::string, Commands::funcPtr> Commands::_messageFunctions;

void Commands::populateMap(void)
{
	_messageFunctions["USER"] = user;
	_messageFunctions["NICK"] = nick;
	_messageFunctions["PASS"] = pass;
	_messageFunctions["CAP"] = cap;
	_messageFunctions["QUIT"] = quit;
}

std::string Commands::callFunction(const std::string cmdName, CommandArgs args)
{
	if (_messageFunctions.find(cmdName) == _messageFunctions.end())
		throw std::runtime_error("Invalid Command Name");
	return (_messageFunctions[cmdName](args));
}