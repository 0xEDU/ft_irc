#include "ft_irc_tests.hpp"

void parseMsg_tests() {
	std::vector<std::string> response;
	std::string request;
	{
		std::vector<std::string> expected;
		expected.push_back("test!~test@test.com");
		expected.push_back("PRIVMSG #channel :Hi!");

		request = ":test!~test@test.com PRIVMSG #channel :Hi!";
		response = parseMsg(request);
		asserteq(response, expected, "TEST = :test!~test@test.com PRIVMSG #channel :Hi!");
	}
}