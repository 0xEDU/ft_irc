#ifndef REPLIES_HPP
#define REPLIES_HPP

#define FTIRC std::string(":ft.irc")
#define CRLF std::string("\r\n")
#define COMMA std::string(",")
#define SPACE std::string(" ")

// 0s
#define RPL_WELCOME(nick, user)                             (FTIRC + " 001 " + user + " :Welcome to the Internet Relay Chat " + nick + "!" + user + "@*" + CRLF)

// 300s
#define RPL_ENDOFWHO(channel)                               (FTIRC + " 315 " + channel + " :End of /WHO list." + CRLF)
#define RPL_CHANNELMODEIS(channel, mode, modeParams)        (FTIRC + " 324 * " + channel + " " + mode + " " + modeParams + CRLF)
#define RPL_NOTOPIC(nick, channel)                          (FTIRC + " 331 " + nick + " " + channel + " :No topic is set" + CRLF)
#define RPL_TOPIC(nick, channel, topic)                     (FTIRC + " 332 " + nick + " " + channel + " :" + topic + CRLF)
#define RPL_WHOREPLY(channel, user, nick, flags, realname)  (FTIRC + " 352 " + channel + " " + user + " 42sp.org.br ft.irc " + nick + " " + flags + ":0 " + realname + CRLF)
#define RPL_NAMREPLY(nick, channel, names)                  (FTIRC + " 353 " + nick + " = " + channel + " : " + names + CRLF)
#define RPL_ENDOFNAMES(nick, channel)                       (FTIRC + " 366 " + nick + " " + channel + " : End of names list" + CRLF)

// 400s
#define ERR_NOSUCHCHANNEL(channel)          (FTIRC + " 403 * " + channel + " :Invalid channel name!" + CRLF)
#define ERR_NOSUCHNICK(recipient)           (FTIRC + " 406 " + recipient + " :No such nick" + CRLF)
#define ERR_NORECIPIENT(user)               (FTIRC + " 411 " + user + " :No recipient to message" + CRLF)
#define ERR_NOTEXTTOSEND(user)              (FTIRC + " 412 " + user + " :No message to send" + CRLF)
#define ERR_NONICKNAMEGIVEN()               (FTIRC + " 431 :No nickname given" + CRLF)
#define ERR_ERRONEUSNICKNAME(nick)          (FTIRC + " 432 * " + nick + " :Nickname is invalid" + CRLF)
#define ERR_NICKNAMEINUSE(nick)             (FTIRC + " 433 * " + nick + " :Nickname is already in use" + CRLF)
#define ERR_NOTONCHANNEL(channel)           (FTIRC + " 442 * " + channel + " :Client not on channel!" + CRLF)
#define ERR_NEEDMOREPARAMS(command, reason) (FTIRC + " 461 * " + command + " :" + reason + CRLF)
#define ERR_ALREADYREGISTERED(user)         (FTIRC + " 462 " + user + " :User already registered" + CRLF)
#define ERR_PASSWDMISMATCH()                (FTIRC + " 464 * :Password was either not given or was incorrect" + CRLF)
#define ERR_BADCHANNELKEY(user, channel)    (FTIRC + " 475 " + user + " " + channel + " :Password for channel was either not given or incorrect" + CRLF)
#define ERR_CHANOPRIVSNEEDED(user, channel) (FTIRC + " 482 " + user + " " + channel + " :You're not a channel operator!" + CRLF)

// Miscellaneous
#define JOIN(user, channel)                             (":" + user + " JOIN " + channel + CRLF)
#define PRIVMSG_BROADCAST(nick, user, channel, topic)   (":" + nick + "!~" + user + "@ft.irc TOPIC " + channel + " "+ topic + CRLF)
#define RPL_PRIVMSG(user, dest, message)                (":" + user + " PRIVMSG " + dest + " :" + message + CRLF)
#define RPL_PARTMSG(nick, user, dest, message)          (":" + nick + "!~" + user + "@* PART " + dest + " :" + message + CRLF)
#define RPL_PARTNOMSG(nick, user, dest)                 (":" + nick + "!" + user + "@* PART " + dest + CRLF)

#endif
