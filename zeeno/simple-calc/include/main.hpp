#pragma once
#ifndef ZEENO_SIMPLE_CALC_MAIN_HPP
#	define ZEENO_SIMPLE_CALC_MAIN_HPP

#	include <iostream>
#	include <stdexcept>
#	include <string_view>
#	include <limits>
#	include <sstream>

template<typename T>
T readFromStream(std::istream& is, std::string_view prompt = "", bool ignoreRest = true) {
	for (int i{0}; i < 3; ++i) {
		T ret;
		std::cout << prompt;
		is >> ret;

		if (!is) {
			is.clear(); //set it to the normal state again
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Try again!" << std::endl;
			continue;
		} else if (ignoreRest) {
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		return ret;
	}
	throw std::runtime_error("What a dumbass!");
}

template<typename T>
std::vector<T> parseLineAsTokens(std::istream& is) {
	std::string line;
	std::getline(is, line);
	std::stringstream ss{line};
	std::vector<T>    arguments;

	while (!ss.eof()) {
		T d;
		ss >> d;

		if (ss.fail()) {
			throw std::runtime_error("invalid input");
		}
		arguments.push_back(d);
	}
	return arguments;
}

#endif
