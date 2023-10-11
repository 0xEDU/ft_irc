#include "ft_irc.hpp"

std::map<std::string, Commands::funcPtr> Commands::_messageFunctions;

void Commands::populateMap()
{
	_messageFunctions["USER"] = user;
	_messageFunctions["NICK"] = nick;
	_messageFunctions["PASS"] = pass;
	_messageFunctions["CAP"] = cap;
	_messageFunctions["QUIT"] = quit;
	_messageFunctions["JOIN"] = join;
	_messageFunctions["LISTC"] = listc;
    _messageFunctions["PRIVMSG"] = privmsg;
    _messageFunctions["KICK"] = kick;
    _messageFunctions["PART"] = part;
    _messageFunctions["WHO"] = who;
    _messageFunctions["MODE"] = mode;
}

std::string Commands::callFunction(const std::string &cmdName, const CommandArgs &args)
{
	if (_messageFunctions.find(cmdName) == _messageFunctions.end())
		return (cmdName + " :Invalid command\r\n");
	return (_messageFunctions[cmdName](args));
}