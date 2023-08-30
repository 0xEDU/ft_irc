#pragma once
#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "ft_irc.hpp"
#include <map>

typedef struct s_CommandArgs {
	Client client;
} CommandArgs;

class Commands
{

	public:

	typedef void (*funcPtr)(CommandArgs);
	static void insertFunction(const std::string cmdName, funcPtr function);
	static void callFunction(const std::string cmdName, CommandArgs args);

	private:

	static std::map<std::string, funcPtr> _messageFunctions;
};

#endif