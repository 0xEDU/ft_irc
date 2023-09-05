#pragma once
#ifndef REPLIES_HPP
#define REPLIES_HPP

#define RPL_WELCOME(nick, user) ":* 001 "+ user + " :Welcome to the Internet Relay Chat " + nick +"!" + user + "@*\r\n"

#define ERR_NICKNAMEINUSE(nick) ":* 433 " + nick + " :Nickname alredy in use\r\n"
#define ERR_ALREADYREGISTERED(user) ":* 462 " + user + " :User alredy registered\r\n"


#endif