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
		poll(fakePoll, CLIENT_LIMIT, TIMEOUT);
		if (fakePoll[0].revents & POLLIN) {
			Client *client = new Client(fakeServer, fakePoll);
			return client;
		}
	}
}

void clientInitialization_test(Client *client) {
	mu_assert(client->getFd() == 4, "FD is correct");
	mu_assert(client->getId() == 1, "Id is correct");
}

MU_TEST(instantiateClient) {
	Client *client = newClient();
	clientInitialization_test(client);
	close(client->getFd());
	delete client;
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(instantiateClient);
}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}