#pragma once
#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "ft_irc.hpp"
#include <map>

struct CommandArgs;

class Commands
{

	public:

	typedef std::string (*funcPtr)(CommandArgs);

	static void 			populateMap(void);
	static std::string 		callFunction(const std::string& cmdName, const CommandArgs& args);
	static std::string		getResponseMessage(const std::string cmdName);

	private:

	static std::map<std::string, funcPtr> _messageFunctions;
};

std::string nick(CommandArgs cArgs);
std::string user(CommandArgs cArgs);
std::string pass(CommandArgs cArgs);
std::string cap(CommandArgs cArgs);
std::string quit(CommandArgs cArgs);
std::string join(CommandArgs cArgs);
std::string privmsg(CommandArgs cArgs);
std::string kick(CommandArgs cArgs);
std::string part(CommandArgs cArgs);

#endif