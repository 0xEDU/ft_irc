#include "ft_irc.hpp"

Message::Message() {}

Message::~Message() {}

Message::Message(std::string prefix, std::string command, std::vector<std::string> args)
	: prefix(prefix), command(command), args(args) {}

Message::Message(const Message &other)
{
	*this = other;
}

Message &Message::operator=(const Message &other)
{
	if (this != &other)
	{
		this->prefix = other.prefix;
		this->command = other.command;
		this->args = other.args;
	}
	return (*this);
}