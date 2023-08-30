#include "Commands.hpp"

std::map<std::string, Commands::funcPtr> Commands::_messageFunctions;

void Commands::insertFunction(const std::string cmdName, Commands::funcPtr function)
{
	_messageFunctions[cmdName] = function;
}

void Commands::callFunction(const std::string cmdName, CommandArgs args)
{
	_messageFunctions[cmdName](args);
}