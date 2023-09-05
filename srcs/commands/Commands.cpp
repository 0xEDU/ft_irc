#include "ft_irc.hpp"

std::map<std::string, std::pair<Commands::funcPtr, std::string*> > Commands::_messageFunctions;

void Commands::populateMap(void)
{
	_messageFunctions["USER"] = std::make_pair<funcPtr, std::string *>(user, NULL);
	_messageFunctions["NICK"] = std::make_pair<funcPtr, std::string *>(nick, NULL);
	_messageFunctions["PASS"] = std::make_pair<funcPtr, std::string *>(pass, NULL);
	_messageFunctions["CAP"] = std::make_pair<funcPtr, std::string *>(cap, NULL);
}

void Commands::callFunction(const std::string cmdName, CommandArgs args)
{
	if (_messageFunctions.find(cmdName) == _messageFunctions.end())
		throw std::runtime_error("Invalid Command Name");
	_messageFunctions[cmdName].first(args);
}

std::string *Commands::getResponseMessage(const std::string cmdName)
{
	return (_messageFunctions[cmdName].second);
}