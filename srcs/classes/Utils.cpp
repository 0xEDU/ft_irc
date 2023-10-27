#include "ft_irc.hpp"
#include <algorithm>
#include <cstdlib>

// Split
std::vector<std::string> Utils::split(std::string &s, std::string delimiter)
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

// Check if the string has unique mode characters
bool Utils::containsUniqueModeCharacters(std::string str) {
	std::string modeCharacters = "+-oitkl";
	if (str.size() > modeCharacters.size())
		return false;
	for (size_t i = 0; i < str.length(); ++i) {
		if (modeCharacters.find(str[i]) == std::string::npos
			|| (str[i] == '+' && i != 0)
			|| (str[i] == '-' && i != 0)) {
			return false;
		}
	}
	std::sort(str.begin(), str.end());
	return std::unique(str.begin(), str.end()) == str.end();
}

bool hasOnlyDigits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

// Check if the modes in the mode string have a corresponding parameter
bool Utils::hasModeCommandsWithParams(std::string modes, std::vector<std::string> modeParams) {
	std::string charactersWithParams = "okl";
	bool shouldNegate = false;
	bool hasNegation = modes.find('-') != std::string::npos;
	if (hasNegation) {
		charactersWithParams = "o";
		shouldNegate = true;
	}
	size_t paramsCount = 0;
	for (size_t i = 0; i < modes.length(); ++i) {
		if (!shouldNegate) {
			if (modes[i] == 'l' && std::strtod(modeParams[paramsCount].c_str(), NULL) <= 0) {
				return false;
			}
			if (modes[i] == 'l' && !hasOnlyDigits(modeParams[paramsCount])) {
				return false;
			}
		}
		if (charactersWithParams.find(modes[i]) != std::string::npos) {
			paramsCount++;
		}
	}
	if (paramsCount != modeParams.size())
		return false;
	return true;
}

// Pollfd operator overloads
bool operator==(const pollfd &lhs, const pollfd &rhs) {
	return (lhs.events == rhs.events && lhs.fd == rhs.fd && lhs.revents == rhs.revents);
};

// Constructor/Destructor
Utils::Utils() {}
Utils::~Utils() {}
