#pragma once
#ifndef REPLIES_HPP
#define REPLIES_HPP

#define JOIN(user, channel) (":" + cArgs.client.getUser() + " JOIN " + cArgs.msg.args[0] + "\r\n")

#define RPL_WELCOME(nick, user) (":* 001 "+ user + " :Welcome to the Internet Relay Chat " + nick + "!" + user + "@*\r\n")
#define RPL_TOPIC(nick, channel, topic) (":* 332 " + nick + " " + channel + " :" + topic + "\r\n")
#define RPL_NAMREPLY(nick, channel, names) (":* 353 " + nick + " = " + channel + " : " + names + "\r\n")
#define RPL_ENDOFNAMES(nick, channel) (":* 366 " + nick + " " + channel + " : End of names list\r\n")

#define ERR_ERRONEUSNICKNAME(nick) (":* 432 * " + nick + " :Nickname is invalid\r\n")
#define ERR_NICKNAMEINUSE(nick) (":* 433 * " + nick + " :Nickname is already in use\r\n")
#define ERR_ALREADYREGISTERED(user) (":* 462 " + user + " :User already registered\r\n")
#define ERR_PASSWDMISMATCH ":* 464 * :Password was either not given or was incorrect\r\n"
#define ERR_NOSUCHCHANNEL(channel) (":* 403 " + channel + " :Invalid channel name!\r\n")

#endif