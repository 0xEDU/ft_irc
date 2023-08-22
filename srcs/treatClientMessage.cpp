#include "ft_irc.hpp"

// void treatClientMessage(int currClientfd)
// {
// 	for (int i = 0; i < 2; i++) {
// 		char buff[BUFFER_SIZE];
// 		std::memset(buff, 0, BUFFER_SIZE);
// 		if (recv(currClientfd, buff, BUFFER_SIZE, 0) < 0)
// 			throw std::runtime_error("Failed to receive message");
// 	}
// 	/* std::exit(0); */
// }

void treatClientMessage(int currClientfd)
{
	while (true)
	{
		char buff[BUFFER_SIZE];
		std::memset(buff, 0, BUFFER_SIZE);
		int nbytes = recv(currClientfd, buff, BUFFER_SIZE, 0);
		// ... handle the nbytes as shown above ...
		if (nbytes < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			else
				throw std::runtime_error("Failed to receive message");
		}
		else if (nbytes == 0)
			break;
		else
		{
			std::cout << "Received: " << buff << std::endl;
			break;
		}
	}
}