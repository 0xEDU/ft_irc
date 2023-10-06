#pragma once
#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "ft_irc.hpp"
#include "classes/Channel.hpp"

struct Message
{
	std::string					prefix;
	std::string					command;
	std::vector<std::string>	args;

	Message();
	Message(const std::string&, const std::string&, const std::vector<std::string>&);
	~Message();
	Message(const Message &other);
	Message &operator=(const Message &other);

    static Message parseMsg(std::string msg);

    static std::pair<std::string, std::vector<Client> >
    processMessage(Message &msg, Client &client, std::vector<Client> &clients, std::vector<Channel> &channels);
};


#endif