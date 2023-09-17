#include "ft_irc.hpp"

std::string receiveData(const Client client)
{
	std::string data;
	// const int maxRetries = 5; // Maximum retries

	while (true)
	{
		char buff[BUFFER_SIZE];
		std::memset(buff, 0, BUFFER_SIZE);

		int nbytes = recv(client.getFd(), buff, BUFFER_SIZE, 0);
		if (nbytes < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				// if (++retryCounter >= maxRetries)
				// {
				// 	std::cout << "Max retries reached, breaking..." << std::endl;
				// 	break;
				// }
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
			std::cout << "Connection closed by client." << std::endl;
			break;
		}
		else
		{
			data.append(buff, nbytes);
		}
	}
	std::cout << std::endl << data << std::endl;
	return data;
}