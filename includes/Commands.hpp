#pragma once
#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "ft_irc.hpp"
#include <map>

typedef struct CommandArgs
{
	Client &client;
	Message msg;
	std::vector<Client> &clients;
}CommandArgs;

class Commands
{

	public:

	typedef std::string (*funcPtr)(CommandArgs);

	static void 			populateMap(void);
	static std::string 		callFunction(const std::string cmdName, CommandArgs args);
	static std::string		getResponseMessage(const std::string cmdName);

	private:

	static std::map<std::string, funcPtr> _messageFunctions;
};

std::string nick(CommandArgs cArgs);
std::string user(CommandArgs cArgs);
std::string pass(CommandArgs cArgs);
std::string cap(CommandArgs cArgs);

#endif