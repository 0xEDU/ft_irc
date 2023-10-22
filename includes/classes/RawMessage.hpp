#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "ft_irc.hpp"
#include "classes/Channel.hpp"

struct RawMessage
{
	std::string					prefix;
	std::string					command;
	std::vector<std::string>	args;

	RawMessage();
	RawMessage(const std::string&, const std::string&, const std::vector<std::string>&);
	~RawMessage();
	RawMessage(const RawMessage &other);
	RawMessage &operator=(const RawMessage &other);

	static RawMessage parseMsg(std::string msg);

	static std::pair<std::string, std::vector<Client> >
	processMessage(RawMessage &msg, Client &client, std::vector<Client> &clients, std::vector<Channel> &channels);
};


#endif