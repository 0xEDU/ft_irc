#include "ft_irc.hpp"

std::string receiveMessage(const Client client)
{
    std::string data;
    int retryCounter = 0;
    const int maxRetries = 5; // Maximum retries

    while (true)
    {
        char buff[BUFFER_SIZE];
        std::memset(buff, 0, BUFFER_SIZE);

        int nbytes = recv(client.getFd(), buff, BUFFER_SIZE, 0);
        if (nbytes < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                if (++retryCounter >= maxRetries)
                {
                    std::cout << "Max retries reached, breaking..." << std::endl;
                    break;
                }
                usleep(10000); // Sleep for 10 ms before retrying
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
            retryCounter = 0; // Reset the retry counter on a successful recv
            data.append(buff, nbytes);
            if (data.find("\n") != std::string::npos) // Assuming '\n' as the end of message
                break;
        }
    }
	std::cout << std::endl << data << std::endl;
    return data;
}