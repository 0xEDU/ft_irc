#ifndef REPLIES_HPP
#define REPLIES_HPP

#define JOIN(user, channel) (":" + user + " JOIN " + channel + "\r\n")
#define PRIVMSG_BROADCAST(nick, user, channel, topic) (":" + nick + "!~" + user + "@ft.irc TOPIC " + channel + " "+ topic + "\r\n")

#define RPL_WELCOME(nick, user) (":ft.irc 001 "+ user + " :Welcome to the Internet Relay Chat " + nick + "!" + user + "@*\r\n")
#define RPL_TOPIC(nick, channel, topic) (":ft.irc 332 " + nick + " " + channel + " :" + topic + "\r\n")
#define RPL_NAMREPLY(nick, channel, names) (":ft.irc 353 " + nick + " = " + channel + " : " + names + "\r\n")
#define RPL_ENDOFNAMES(nick, channel) (":ft.irc 366 " + nick + " " + channel + " : End of names list\r\n")
#define RPL_PRIVMSG(user, dest, message) (":" + user + " PRIVMSG " + dest + " :" + message + "\r\n")
#define RPL_PARTMSG(nick, user, dest, message) (":" + nick + "!~" + user + "@* PART " + dest + " :" + message + "\r\n")
#define RPL_PARTNOMSG(nick, user, dest) (":" + nick + "!" + user + "@* PART " + dest + "\r\n")
#define RPL_WHOREPLY(channel, user, nick, flags, realname) (":ft.irc 352 " + channel + " " + user + " 42sp.org.br ft.irc " + nick + " " + flags + ":0 " + realname + "\r\n")
#define RPL_ENDOFWHO(channel) (":ft.irc 315 " + channel + " :End of /WHO list.\r\n")
#define RPL_CHANNELMODEIS(channel, mode, modeParams) (":ft.irc 324 * " + channel + " " + mode + " " + modeParams + "\r\n")
#define RPL_NOTOPIC(nick, channel) (":ft.irc 331 " + nick + " " + channel + " :No topic is set\r\n")


#define ERR_ERRONEUSNICKNAME(nick) (":ft.irc 432 * " + nick + " :Nickname is invalid\r\n")
#define ERR_NICKNAMEINUSE(nick) (":ft.irc 433 * " + nick + " :Nickname is already in use\r\n")
#define ERR_ALREADYREGISTERED(user) (":ft.irc 462 " + user + " :User already registered\r\n")
#define ERR_PASSWDMISMATCH ":ft.irc 464 * :Password was either not given or was incorrect\r\n"
#define ERR_NOSUCHCHANNEL(channel) (":ft.irc 403 * " + channel + " :Invalid channel name!\r\n")
#define ERR_NEEDMOREPARAMS(command, reason) (":ft.irc 461 * " + command + " :" + reason + "\r\n")
#define ERR_NOTONCHANNEL(channel) (":ft.irc 442 * " + channel + " :Client not on channel!\r\n")
#define ERR_CHANOPRIVSNEEDED(user, channel) (":ft.irc 482 " + user + " " + channel + " :You're not a channel operator!\r\n")
#define ERR_BADCHANNELKEY(user, channel) (":ft.irc 475 " + user + " " + channel + " :Password for channel was either not given or incorrect\r\n")

#endif
