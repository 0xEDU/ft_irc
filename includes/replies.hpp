#pragma once
#ifndef REPLIES_HPP
#define REPLIES_HPP

#define RPL_WELCOME(nick, user) ":* 001 "+ user + " :Welcome to the Internet Relay Chat " + nick +"!" + user + "@*\r\n"

#define ERR_ERRONEUSNICKNAME(nick) ":* 432 * " + nick + " :Nickname is invalid\r\n"
#define ERR_NICKNAMEINUSE(nick) ":* 433 * " + nick + " :Nickname is alredy in use\r\n"
#define ERR_ALREADYREGISTERED(user) ":* 462 " + user + " :User alredy registered\r\n"
#define ERR_PASSWDMISMATCH ":* 464 * :Password was either not given or was incorrect\r\n"

#endif