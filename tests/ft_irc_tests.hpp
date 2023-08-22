#pragma once
#ifndef FT_IRC_TESTS_HPP
#define FT_IRC_TESTS_HPP

#include "ft_irc.hpp"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define END "\033[0m"

void	assert(bool result, bool expected, const char *test);
void	clientTests(void);
#endif