#pragma once
#ifndef REPLIES_HPP
#define REPLIES_HPP

#define JOIN(user, channel) (":" + cArgs.client.getUser() + " JOIN " + cArgs.msg.args[0] + "\r\n")

#define RPL_WELCOME(nick, user) (":* 001 "+ user + " :Welcome to the Internet Relay Chat " + nick + "!" + user + "@*\r\n")
#define RPL_TOPIC(nick, channel, topic) (":* 332 " + nick + " " + channel + " :" + topic + "\r\n")
#define RPL_NAMREPLY(nick, channel, names) (":* 353 " + nick + " = " + channel + " : " + names + "\r\n")
#define RPL_ENDOFNAMES(nick, channel) (":* 366 " + nick + " " + channel + " : End of names list\r\n")
#define RPL_PRIVMSG(nick, user, dest, message) (":" + nick + "!~" + user + "@* PRIVMSG " + dest + " :" + message + "\r\n")
#define RPL_PARTMSG(nick, user, dest, message) (":" + nick + "!" + user + "@* PART " + dest + " :" + message + "\r\n")
#define RPL_PARTNOMSG(nick, user, dest) (":" + nick + "!" + user + "@* PART " + dest + "\r\n")
#define RPL_WHOREPLY(channel, user, nick, flags, realname) (":* 352 * " + channel + " " + user + " * * " + nick + " " + flags + ":0 " + realname + "\r\n")
#define RPL_ENDOFWHO(channel) (":* 315 * " + channel + " :End of /WHO list\r\n")
#define RPL_CHANNELMODEIS(user, channel, mode, modeParams) (":* 324 " + user + " " + channel + " " + mode + modeParams + "\r\n")

#define ERR_ERRONEUSNICKNAME(nick) (":* 432 * " + nick + " :Nickname is invalid\r\n")
#define ERR_NICKNAMEINUSE(nick) (":* 433 * " + nick + " :Nickname is already in use\r\n")
#define ERR_ALREADYREGISTERED(user) (":* 462 " + user + " :User already registered\r\n")
#define ERR_PASSWDMISMATCH ":* 464 * :Password was either not given or was incorrect\r\n"
#define ERR_NOSUCHCHANNEL(channel) (":* 403 * " + channel + " :Invalid channel name!\r\n")
#define ERR_NEEDMOREPARAMS(command, reason) (":* 461 " + command + " :" + reason + "\r\n")
#define ERR_NOTONCHANNEL(channel) (":* 442 * " + channel + " :Client not on channel!\r\n")
#define ERR_CHANOPRIVSNEEDED(user, channel) (":* 482 " + user + " " + channel + " :You're not a channel operator!\r\n")

#endif