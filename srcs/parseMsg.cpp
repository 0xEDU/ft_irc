#include "ft_irc.hpp"

std::vector<std::string> parseMsg(std::string msg)
{
	std::string prefix = "";
	//std::vector<std::string> trailing;
	std::vector<std::string> result;

	if (msg.empty())
		throw std::logic_error("Empty line.");
	if (msg[0] == ':')
	{
		prefix = msg.substr(1, msg.find(' ') - 1);
		msg = msg.substr(msg.find(' ') + 1 , msg.size() - 1);
		result.push_back(prefix);
		result.push_back(msg);
	}
	return (result);
}
