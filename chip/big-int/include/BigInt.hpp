#pragma once
#ifndef CHIP_BIG_INT_HPP
#	define CHIP_BIG_INT_HPP

#	include <iostream>

using namespace std;

class BigInt {
private:
	string value{"0"};

public:
	// Constructors:
	BigInt() = default;
	BigInt(const BigInt&);
	BigInt(const uint64_t&);
	BigInt(const string&);

	// Utility:
	static bool           is_valid_number(const string&); // Control if input is number
	void                  add_leading_zeroes(string&, size_t) const;
	void                  strip_leading_zeroes(string&) const;
	tuple<string, string> get_larger_and_smaller(const string&, const string&) const;
	string                reverse_string(const string&) const;
	string                get_value() const; // Getter

	// Relational operators:
	bool operator==(const BigInt&) const;
	bool operator==(const uint64_t&) const;
	bool operator==(const string&) const;

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
ostream& operator<<(ostream& os, const BigInt& num);

#endif
