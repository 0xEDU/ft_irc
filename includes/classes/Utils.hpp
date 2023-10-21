#ifndef FT_IRC_UTILS_HPP
#define FT_IRC_UTILS_HPP

#include "ft_irc.hpp"

class Utils {
private:
	Utils();
	~Utils();

public:
	static std::vector<std::string> split(std::string &s, std::string& delimiter);
};

bool operator==(const pollfd &lhs, const pollfd &rhs);
#endif
