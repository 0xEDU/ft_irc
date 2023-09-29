#include "ft_irc.hpp"

std::string receiveData(Client &client)
{
	std::string data;

	char buff[BUFFER_SIZE];
	std::memset(buff, 0, BUFFER_SIZE);

	long nbytes = recv(client.getFd(), buff, BUFFER_SIZE, 0);
	if (nbytes == 0)
		client.setShouldEraseClient(true);
	else
		data.append(buff, nbytes);
    std::cout << "RECEIVED: " << data << std::endl;
	return data;
}