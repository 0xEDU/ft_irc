#pragma once
#ifndef COMMAND_ARGS_HPP
#define COMMAND_ARGS_HPP

#include "ft_irc.hpp"

struct CommandArgs
{
	Client &client;
	Message msg;
	std::vector<Client> &clients;
	
	CommandArgs(Client &c, Message m, std::vector<Client> &v);
	~CommandArgs();
};

#endif