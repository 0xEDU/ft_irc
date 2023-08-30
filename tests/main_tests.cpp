#include "ft_irc_tests.hpp"
#include "minunit.h"

int value = 1;

static void testFunction(CommandArgs cArgs) {
	(void)cArgs;
	value++;
	return;
}

MU_TEST(insertAndExecuteFunctionFromCommandsMap) { // not a good name
	// given:
	void (*f)(CommandArgs) = testFunction;
	CommandArgs mockArgs = (CommandArgs) {};

	// when:
	Commands::insertFunction("TEST", f);
	Commands::callFunction("TEST", mockArgs);

	// then:
	mu_check(value == 2);
}

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