#include "ft_irc_tests.hpp"
#include "minunit.h"

MU_TEST(parseMsg) {
	Message response;
	std::string request;
	{
		std::vector<std::string> expectedArgs;
		expectedArgs.push_back("#channel");
		expectedArgs.push_back("Hi!");

		request = ":test!~test@test.com PRIVMSG #channel :Hi!";
		response = parseMsg(request);
		mu_check(response.prefix == std::string("test!~test@test.com"));
		mu_check(response.command == std::string("PRIVMSG"));
		mu_check(response.args == expectedArgs);
	}
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(parseMsg);
	MU_RUN_TEST(insertAndExecuteFunctionFromCommandsMap);
}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}