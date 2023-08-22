#include "ft_irc_tests.hpp"

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
	assert(client->getFd(), 4, "FD is correct");
	assert(client->getId(), 1, "Id is correct");
}

void	clientTests(void) {
	Client *client = newClient();
	clientInitialization_test(client);
	close(client->getFd());
	delete client;
}