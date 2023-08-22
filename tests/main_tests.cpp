#include "ft_irc_tests.hpp"

void assert(bool result, bool expected, const char *test) {
	if (result == expected) {
		std::cout << "[" << GREEN << "OK" << END << "]"
		<< " " << test << std::endl;
	} else {
		std::cout << "[" << RED << "KO" << END << "]"
		<< " " << test << std::endl;
		std::exit(-1);
	}
	return ;
}

int main(void) {
	clientTests();
	return (0);
}