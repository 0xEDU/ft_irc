#include "ft_irc.hpp"

std::vector<std::string> split(const std::string &s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::stringstream ss(s);

	while (std::getline(ss, token, delimiter))
		tokens.push_back(token);
	return tokens;
}