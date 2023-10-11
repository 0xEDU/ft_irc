#include "ft_irc_tests.hpp"
#include "minunit.h"

Client *newClient(void) {
	int port = 2000;
	pollfd fakePoll[CLIENT_LIMIT];

	int fakeServer = setupTCP(port);
	fakePoll[0].fd = fakeServer;
	std::memset(fakePoll, 0, sizeof(pollfd) * CLIENT_LIMIT);
	for (int i = 0; i < CLIENT_LIMIT; i++)
	{
		fakePoll[i].fd = -1;
		fakePoll[i].events = POLLIN;
	}
	fakePoll[0].fd = fakeServer;
	std::cout << GREEN << "Waiting for client connection" << END << std::endl;
	while (true) {
		poll(fakePoll, CLIENT_LIMIT, TIMEOUT_MS);
		if (fakePoll[0].revents & POLLIN) {
			Client *client = new Client(fakeServer, fakePoll);
			return client;
		}
	}
}

Client *client = newClient();

MU_TEST(instantiateClient) {
	mu_assert(client->getFd() == 4, "FD is correct");
	mu_assert(client->getId() == 1, "Id is correct");
}
MU_TEST(callWrongCMD) {
	// given:
	std::vector<std::string> msgArgs;
	msgArgs.push_back(std::string("test_name"));
	RawMessage mockMsg;
	mockMsg.prefix = "";
	mockMsg.command = "NAME";
	mockMsg.args = msgArgs;
	Client &cl = *client;
	CommandArgs mockArgs = (CommandArgs) {
		.client = cl,
		.msg = mockMsg
	};
	std::string expected = "Invalid Command Name";

	// when:
	try {
		Commands::callFunction("TEST", mockArgs);
	} catch (std::runtime_error &e) {
		// then:
		mu_assert(e.what() == expected, "Wrong command");
	}
}

MU_TEST(callCmdUSER) {
	// given:
	std::vector<std::string> msgArgs;
	msgArgs.push_back(std::string("test_user"));
	msgArgs.push_back(std::string("0"));
	msgArgs.push_back(std::string("*"));
	msgArgs.push_back(std::string("real name"));
	RawMessage mockMsg;
	mockMsg.prefix = "";
	mockMsg.command = "USER";
	mockMsg.args = msgArgs;
	Client &cl = *client;
	CommandArgs mockArgs = (CommandArgs) {
		.client = cl,
		.msg = mockMsg
	};

	// when:
	Commands::callFunction("USER", mockArgs);

	// then:
	mu_assert(client->getUser() == "test_user", "USER is correct");
	mu_assert(client->getRealName() == "real name", "REALNAME is correct");
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(instantiateClient);
	Commands::populateMap();
	MU_RUN_TEST(callWrongCMD);
	MU_RUN_TEST(callCmdUSER);
}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	close(client->getFd());
	delete client;
	return MU_EXIT_CODE;
}