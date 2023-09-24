#pragma once
#ifndef COMMAND_ARGS_HPP
#define COMMAND_ARGS_HPP

#include "ft_irc.hpp"

struct CommandArgs
{
	Client &client;
	Message msg;
	std::vector<Client> &clients;
	std::vector<Channel> &channels;
	
	CommandArgs(Client &client, const Message& msg, std::vector<Client> &clients, std::vector<Channel> &channels);
	~CommandArgs();
};

#endif