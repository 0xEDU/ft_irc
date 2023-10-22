#include "ft_irc.hpp"

std::vector<std::string> Utils::split(std::string &s, std::string& delimiter)
{
	std::vector<std::string> tokens;
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		tokens.push_back(s.substr(pos_start, pos_end - pos_start));
		pos_start = pos_end + delim_len;
	}   
	tokens.push_back(s.substr(pos_start));
	tokens.erase(std::remove(tokens.begin(), tokens.end(), ""), tokens.end());
	return tokens;
}


// Pollfd operator overloads
bool operator==(const pollfd &lhs, const pollfd &rhs) {
	return (lhs.events == rhs.events && lhs.fd == rhs.fd && lhs.revents == rhs.revents);
};


// Constructor/Destructor
Utils::Utils() {}
Utils::~Utils() {}