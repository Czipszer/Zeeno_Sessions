#include "BigInt.hpp"

#include <ranges>
#include <sstream>
#include <unordered_map>

std::uint8_t char2nibble(char c) {
	switch (c) {
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'a':
	case 'A':
		return 10;
	case 'b':
	case 'B':
		return 11;
	case 'c':
	case 'C':
		return 12;
	case 'd':
	case 'D':
		return 13;
	case 'e':
	case 'E':
		return 14;
	case 'f':
	case 'F':
		return 15;
	}
	throw std::runtime_error("Not a hex character");
}

char nibble2char(std::uint8_t nibble) {
	switch (nibble) {
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 10:
		return 'a';
	case 11:
		return 'b';
	case 12:
		return 'c';
	case 13:
		return 'd';
	case 14:
		return 'e';
	case 15:
		return 'f';
	}
	throw("Not a nibble value");
}

BigInt::BigInt(std::string_view s, Base b) {
	if (b != Base::Hex) {
		throw std::runtime_error("Only a hex base is supported");
	}

	// Each 8 characters makes 1 int and even for 1 character, we need to allocate 1 int
	_data.resize(s.size() / (bytes * 2) + 1, 0);

	// for each character
	for (size_t counter{0}; counter < s.size(); ++counter) {
		// compute index in reverse
		size_t index = s.size() - counter - 1;

		std::uint8_t shift       = (counter % (bytes * 2)) * 4;   // This tells what part of int the nibble is
		size_t       targetIndex = counter / (bytes * 2);         // This tells which int it is
		std::uint8_t nibble      = char2nibble(s[index]);         // Convert character into the number
		_data[targetIndex] += static_cast<Type>(nibble) << shift; // Add it to the right place
	}
}

BigInt BigInt::operator+(BigInt other) {
	BigInt ret; // Create an object we will return

	const size_t safeSize = std::max(_data.size(), other._data.size()) + 1;
	_data.resize(safeSize);
	other._data.resize(safeSize);
	ret._data.resize(safeSize);

	// Normal version
	Type carry{0};

	for (size_t i{0}; i < safeSize; ++i) {
		Type a      = _data[i];
		Type b      = other._data[i];
		Type result = a + b + carry;

		if (carry == 0) {
			carry = ((result < a || result < b) ? 1 : 0);
		} else {
			carry = ((result <= a || result <= b) ? 1 : 0);
		}

		ret._data[i] = result;
	}

	return ret.normalize();
}

std::string BigInt::to_string(Base b) const {
	if (b != Base::Hex) {
		throw std::runtime_error("Only hex base is supported");
	}

	std::string ret;
	ret.reserve(_data.size() * bytes * 2);

	for (auto bucket : _data | std::views::reverse) {
		// Each byte produces 2 characters
		for (int i{bytes * 2}; i--;) {
			std::uint8_t nibble = (bucket & highNibble) >> (bytes * 8 - 4);
			if (ret.size() || nibble) { // skip leading zeroes
				ret.push_back(nibble2char(nibble));
			}
			bucket <<= 4;
		}
	}

	return ret;
}

BigInt& BigInt::normalize() {
	while (_data.size() && _data.back() == 0) {
		_data.pop_back();
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const BigInt& big) {
	// std::cout is of type std::ostream, so think of `os` as a std::cout
	os << big.to_string(BigInt::Base::Hex);
	return os;
}
