#pragma once
#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "ft_irc.hpp"
#include <map>

typedef struct CommandArgs
{
	Client &client;
	Message msg;
}CommandArgs;

class Commands
{

	public:

	typedef void (*funcPtr)(CommandArgs);
	static void populateMap(void);
	static void callFunction(const std::string cmdName, CommandArgs args);

	private:

	static std::map<std::string, funcPtr> _messageFunctions;
};

void nick(CommandArgs cArgs);
void name(CommandArgs cArgs);
void user(CommandArgs cArgs);
void pass(CommandArgs cArgs);

#endif