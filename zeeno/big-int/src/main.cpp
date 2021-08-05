#include <cstdlib>
#include <iostream>
#include <random>
#include <ranges>
#include <sstream>

#include "BigInt.hpp"
#include "TestSet.hpp"

BigInt testStep(const BigInt& number) {
	if (number % 2 == 0) {
		return number / 2;
	}
	return number * 3 + 1;
}

void runTest(const std::vector<BigInt>& sequence) {
	if (sequence.empty()) {
		throw std::out_of_range("Sequence can not be empty");
	}

	BigInt number{sequence.front()};
	for (const BigInt& item : sequence) {
		if (number != item) {
			std::stringstream ss;
			ss << "There is a error in your code somewhere. Expected " << item << " but got " << number;
			throw std::runtime_error(ss.str().c_str());
		}

		number = testStep(number);
	}
}

void runTests() {
	for (size_t i{0}; i < TestSet::data.size(); ++i) {
		std::cout << "Running test [" << i + 1 << "/" << TestSet::data.size() << "]: ";
		runTest(TestSet::data[i]);
		std::cout << "SUCCESS" << std::endl;
	}
}

int main(int, char**) {
	try {
		runTests();
		std::cout << "Congratulations, all tests passed" << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Your program is faulty: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Since your program looks like it works correctly, I will generate for you another sequence" << std::endl;

	std::random_device                           generator;
	std::uniform_int_distribution<std::uint16_t> distribution(std::numeric_limits<std::uint16_t>::max() >> 2, std::numeric_limits<std::uint16_t>::max());

	BigInt number{distribution(generator)};
	std::cout << "{";
	while (number != 1) {
		std::cout << "0x" << number << ", ";
		std::cout.flush();

		number = testStep(number);
	}
	std::cout << "0x1}" << std::endl;

	return EXIT_SUCCESS;
}