#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>

#include "BigInt.hpp"

using namespace std;

// Utility:
bool BigInt::is_valid_number(const string& num) {
	for (char digit : num) {
		if (digit < '0' or digit > '9') {
			return false;
		}
	}
	return true;
}

void BigInt::add_leading_zeroes(string& num, size_t num_zeroes) const {
	string temp(num_zeroes, '0');
	num = temp + num;
}

void BigInt::strip_leading_zeroes(string& num) const {
	size_t i{};

	for (i = 0; i < num.size(); i++) {
		if (num[i] != '0') {
			break;
		}
	}

	if (i == num.size()) {
		num = "0";
	} else {
		num = num.substr(i);
	}
}

tuple<string, string> BigInt::get_larger_and_smaller(const string& num1, const string& num2) const {
	string larger, smaller;

	if (num1.size() > num2.size() or (num1.size() == num2.size() and num1 > num2)) {
		larger  = num1;
		smaller = num2;
	} else {
		larger  = num2;
		smaller = num1;
	}

	// pad the smaller number with zeroes
	add_leading_zeroes(smaller, larger.size() - smaller.size());

	return make_tuple(larger, smaller);
}

string BigInt::reverse_string(const string& reverse) const {
	string reversed;

	for (long i = reverse.size() - 1; i >= 0; i--) {
		reversed.push_back(reverse[i]);
	}

	return reversed;
}

string BigInt::get_value() const {
	return value;
}

// Constructors:
/* It is define as default
BigInt::BigInt(const BigInt& num) {
	value = num.value;
}
*/

BigInt::BigInt(const uint64_t num) {
	value = to_string(num);
}

BigInt::BigInt(const std::string& num) {
	string magnitude;
	if (num[0] == '+' or num[0] == '-') { // check for sign
		magnitude = num.substr(1);
	} else { // if no sign is specified
		magnitude = num;
	}

	if (is_valid_number(magnitude)) {
		value = magnitude;
	} else {
		throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
	}
}

// Relational operators:
bool BigInt::operator==(const BigInt& num) const {
	return *this == num.get_value();
}

bool BigInt::operator==(const uint64_t& num) const {
	return *this == BigInt(num);
}

bool BigInt::operator==(const string& num) const {
	return *this == BigInt(num);
}

// Binary arithmetic operators:
BigInt BigInt::operator+(const BigInt& num) const {
	// identify the numbers as `larger` and `smaller`
	string larger, smaller;
	tie(larger, smaller) = get_larger_and_smaller(this->get_value(), num.get_value());

	BigInt    result{""}; // the resultant sum and the value is cleared as the digits will be appended
	short int carry{0};

	// add the two values
	for (long i = larger.size() - 1; i >= 0; i--) { //Warning co stím -> inicializování: Převod z: size_t na: long, může dojít ke ztrátě dat.MSVC(C4267)
		short int sum{0};
		sum          = larger[i] - '0' + smaller[i] - '0' + carry;
		result.value = to_string(sum % 10) + result.value;
		carry        = sum / (short int) 10;
	}
	if (carry) {
		result.value = to_string(carry) + result.value;
	}

	return result;
}

BigInt BigInt::operator*(const BigInt& num) const {
	if (*this == 0 or num == 0)
		return BigInt(0);
	if (*this == 1)
		return num;
	if (num == 1)
		return *this;

	string larger, smaller;
	tie(larger, smaller) = get_larger_and_smaller(this->get_value(), num.value);

	strip_leading_zeroes(smaller);

	BigInt    result{""}; // the resultant multipication and the value is cleared as the digits will be appended
	short int carry{0};

	for (long i = smaller.size() - 1; i >= 0; i--) { //Warning co stím -> inicializování: Převod z: size_t na: long, může dojít ke ztrátě dat.MSVC(C4267)
		BigInt temp{""};
		size_t step{smaller.size() - 1 - i};

		for (auto k = 0; k < step; k++) {
			temp.value = to_string(0) + temp.value;
		}

		for (long ii = larger.size() - 1; ii >= 0; ii--) { //Warning co stím -> inicializování: Převod z: size_t na: long, může dojít ke ztrátě dat.MSVC(C4267)
			short int mul{0};
			mul        = (larger[ii] - '0') * (smaller[i] - '0') + carry;
			temp.value = to_string(mul % 10) + temp.value;
			carry      = mul / (short int) 10;
		}

		if (carry) {
			temp.value = to_string(carry) + temp.value;
		}

		result = result + temp;
	}
	return result;
}

BigInt BigInt::operator%(const BigInt& num) const {
	if (num == 0) {
		throw std::logic_error("Attempted division by zero");
	}
	if (num == 1 or num == *this) {
		return BigInt{0};
	}

	BigInt remainder{};

	remainder = stoull(this->get_value()) % stoull(num.get_value());

	strip_leading_zeroes(remainder.value);

	return remainder;
}

// 3n + 1 problem
BigInt BigInt::operator*(const int& num) const {
	BigInt temp{to_string(num)};

	return *this * temp;
}

BigInt BigInt::operator%(const int& num) const {
	BigInt temp{to_string(num)};

	return *this % temp;
}

BigInt BigInt::operator+(const int& num) const {
	BigInt temp{to_string(num)};

	return *this + temp;
}
/*
BigInt BigInt::operator-(const int& num) const {
	BigInt temp{to_string(num)};

	return *this - temp;
}
*/
BigInt BigInt::operator/(const int& num) const {
	BigInt result{""};

	size_t size = (this->get_value().size());

	if (size < 2) {
		result = to_string(stoll(this->get_value()) / 2);
	}

	for (long i = size - 2; i >= 0; i--) {
		long long int temp = stoll(this->get_value().substr(i, 2));

		if (i == 0) {
			result.value = result.value + reverse_string(to_string(temp / 2));
		} else {
			result.value.push_back(((temp / 2) % 10) + '0');
		}
	}

	return reverse_string(result.value);
}

// iostream
ostream& operator<<(std::ostream& os, const BigInt& num) {
	os << num.get_value();
	return os;
}
