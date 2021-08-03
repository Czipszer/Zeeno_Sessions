#include <cstdlib>
#include <iostream>

#include "BigInt.hpp"

int main(int, char**) {
	BigInt a{"10101010101010101010101010101", BigInt::Base::Hex};
	BigInt b{"102030405060708090a0b0c0d0e0f", BigInt::Base::Hex};

	std::cout << a + b << std::endl;
	std::cout << a + b << std::endl;
	std::cout << a + a + b << std::endl;

	return EXIT_SUCCESS;
}