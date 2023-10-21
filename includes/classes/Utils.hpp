#ifndef FT_IRC_UTILS_HPP
#define FT_IRC_UTILS_HPP

#include "ft_irc.hpp"

class Utils {
private:
	Utils();
	~Utils();

public:
	static std::vector<std::string> split(const std::string &s, const std::string& delimiter = " ");

	// Pollfd operator overloads
};


bool operator==(const pollfd &lhs, const pollfd &rhs);
#endif
