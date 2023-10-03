#include "ft_irc.hpp"

Message::Message() {}

Message::~Message() {}

Message::Message(const std::string& prefix, const std::string& command, const std::vector<std::string>& args)
	: prefix(prefix), command(command), args(args) {}

Message::Message(const Message &other)
{
	*this = other;
}

Message &Message::operator=(const Message &other)
{
	if (this != &other)
	{
		this->prefix = other.prefix;
		this->command = other.command;
		this->args = other.args;
	}
	return (*this);
}
Message Message::parseMsg(std::string msg)
{
    std::string prefix;
    std::vector<std::string> args;

    if (msg.empty())
        throw std::logic_error("Empty line.");
    if (msg[0] == ':')
    {
        prefix = msg.substr(1, msg.find(' ') - 1);
        msg = msg.substr(msg.find(' ') + 1 , msg.size() - 1);
    }
    std::size_t found = msg.find(" :");
    if (found != std::string::npos)
    {
        std::string trailing = msg.substr(found + 2, msg.size() - 1);
        msg = msg.substr(0, found);
        args = split(msg);
        args.push_back(trailing);
    }
    else
        args = split(msg);
    std::string command = args[0];
    args.erase(args.begin());
    return (Message(prefix, command, args));
}
std::pair<std::string, std::vector<Client> >
Message::processMessage(Message &msg, Client &client, std::vector<Client> &clients, std::vector<Channel> &channels)
{
    std::vector<Client> broadcastList;
    CommandArgs cArgs = CommandArgs(client, msg, clients, channels, broadcastList);

    return (std::make_pair(Commands::callFunction(msg.command, cArgs), broadcastList));
}
