#pragma once
#ifndef ZEENO_HELLO_WORLD_MAIN_HPP
#	define ZEENO_HELLO_WORLD_MAIN_HPP

#	include <iostream>
#	include <stdexcept>
#	include <string_view>

template<typename T>
T readFromCin(std::string_view prompt = "") {
	for (int i{0}; i < 3; ++i) {
		T ret;
		std::cout << prompt;
		std::cin >> ret;

		if (!std::cin) {
			std::cin.clear(); //set it to the normal state again
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Try again!" << std::endl;
			continue;
		} else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		return ret;
	}
	throw std::runtime_error("What a dumbass!");
}
#endif
