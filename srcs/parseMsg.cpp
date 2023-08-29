#include "ft_irc.hpp"

Message parseMsg(std::string msg)
{
	std::string prefix = "";
	std::vector<std::string> args;

	if (msg.empty())
		throw std::logic_error("Empty line.");
	if (msg[0] == ':')
	{
		prefix = msg.substr(1, msg.find(' ') - 1);
		msg = msg.substr(msg.find(' ') + 1 , msg.size() - 1);
	}
	std::size_t found = msg.find(" :");
	if (found != std::string::npos)
	{
		std::string trailing = msg.substr(found + 2, msg.size() - 1);
		msg = msg.substr(0, found);
		args = split(msg);
		args.push_back(trailing);
	}
	else
		args = split(msg);
	std::string command = args[0];
	args.erase(args.begin());
	return (Message(prefix, command, args));
}
