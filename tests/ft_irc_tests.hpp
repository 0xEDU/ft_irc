#ifndef FT_IRC_TESTS_HPP
#define FT_IRC_TESTS_HPP

#include "ft_irc.hpp"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define END "\033[0m"

template<typename T>
std::ostream &operator<<(std::ostream &o, std::vector<T> &v) {
	typename std::vector<T>::iterator it = v.begin();
	for (; it != v.end(); it++) {
		o << *it << " ";
	}
	o << std::endl;
	return o;

}

template<typename T>
void asserteq(T result, T expected, const char *test) {
	if (result == expected) {
		std::cout << "[" << GREEN << "OK" << END << "]"
		<< " " << test << std::endl;
	} else {
		std::cout << "[" << RED << "KO" << END << "]"
		<< " " << test << std::endl
		<< "Expected: \n" << expected << std::endl
		<< "Result: \n" << result;
		std::exit(-1);
	}
	return ;
};

void	assert(bool result, bool expected, const char *test);
#endif