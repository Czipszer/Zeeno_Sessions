#pragma once
#ifndef CHIP_BIG_INT_HPP
#	define CHIP_BIG_INT_HPP

#	include <iostream>

class BigInt {
private:
	std::string _value{"0"};

public:
	// Constructors:
	BigInt()              = default;
	BigInt(const BigInt&) = default;
	BigInt(const uint64_t);
	BigInt(const std::string&);

	// Utility:
	static bool                          is_valid_number(const std::string&); // Control if input is number
	void                                 add_leading_zeroes(std::string&, size_t) const;
	void                                 strip_leading_zeroes(std::string&) const;
	std::tuple<std::string, std::string> get_larger_and_smaller(const std::string&, const std::string&) const;
	std::string                          reverse_string(const std::string&) const;
	std::string                          get_value() const; // Getter

	// Relational operators:
	bool operator==(const BigInt&) const;
	bool operator==(const uint64_t) const;
	bool operator==(const std::string&) const;

	// Binary arithmetic operators:
	BigInt operator+(const BigInt&) const;
	//BigInt operator-(const BigInt&) const;
	BigInt operator*(const BigInt&) const;
	BigInt operator%(const BigInt&) const;

	// 3n + 1 problem
	BigInt operator*(const int&) const;
	BigInt operator%(const int&) const;
	BigInt operator+(const int&) const;
	//BigInt operator-(const int&) const;
	BigInt operator/(const int&) const;
};

// iostream
std::ostream& operator<<(std::ostream& os, const BigInt& num);

#endif
