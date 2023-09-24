#include "ft_irc.hpp"


std::string receiveData(Client &client)
{
	std::string data;
	// const int maxRetries = 5; // Maximum retries

	while (true)
	{
		char buff[BUFFER_SIZE];
		std::memset(buff, 0, BUFFER_SIZE);

		long nbytes = recv(client.getFd(), buff, BUFFER_SIZE, 0);
		if (nbytes < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				if (data.find("\r\n") != std::string::npos)
					break;
				continue;
			}
			else
			{
				std::cerr << "recv() failed with errno: " << errno << std::endl;
				throw std::runtime_error("Failed to receive message");
			}
		}
		else if (nbytes == 0)
		{
            client.setShouldEraseClient(true);
            break;
		}
		else
		{
			data.append(buff, nbytes);
		}
	}
	return data;
}