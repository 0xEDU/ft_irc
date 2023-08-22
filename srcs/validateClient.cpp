#include "ft_irc.hpp"

bool validateClient(Client &client)
{
	if (registerClient(client))
		return (true);
	// if (client.getName().empty())
	// if (client.getNick().empty())
	return (false);
}