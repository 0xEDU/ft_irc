#include "ft_irc.hpp"

std::vector<std::string> Utils::split(const std::string &s, const std::string& delimiter)
{
	std::vector<std::string> tokens;
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		tokens.push_back(s.substr(pos_start, pos_end - pos_start));
		pos_start = pos_end + delim_len;
	}
	tokens.push_back(s.substr(pos_start));
	return tokens;
}

Utils::Utils() {}
Utils::~Utils() {}