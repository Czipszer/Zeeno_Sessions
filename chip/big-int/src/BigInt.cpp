#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>

#include "BigInt.hpp"

using namespace std;

// Utility:
bool BigInt::is_valid_number(const string& num) {
	for (char digit : num) {
		//if (digit < '0' or digit > '9') {
		if (!isdigit(digit)) {
			return false;
		}
	}
	return true;
}

void BigInt::add_leading_zeroes(string& num, size_t num_zeroes) {
	string temp(num_zeroes, '0');
	num = temp + num;
}

void BigInt::strip_leading_zeroes(string& num) {
	auto i = num.find_first_not_of('0');

	if (i != string::npos) {
		num = num.substr(i);
	} else {
		num = "0";
	}
}

tuple<string, string> BigInt::get_larger_and_smaller(const string& num1, const string& num2) {
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

tuple<BigInt, BigInt> BigInt::divide(const BigInt& dividend, const BigInt& divisor) {
	BigInt quotient{1}, remainder, temp{divisor};

	while (temp < dividend) {
		quotient = quotient + 1;
		temp     = temp + divisor;
	}

	if (temp > dividend) {
		quotient  = quotient - 1;
		remainder = dividend - (temp - divisor);
	}

	return make_tuple(quotient, remainder);
}

string BigInt::reverse_string(const string& reverse) {
	string reversed;

	for (long i = reverse.size() - 1; i >= 0; i--) {
		reversed.push_back(reverse[i]);
	}

	return reversed;
}

string BigInt::get_value() const {
	return _value;
}

// Constructors:
/* It is define as default
BigInt::BigInt(const BigInt& num) {
	value = num.value;
}
*/

BigInt::BigInt(const uint64_t num) {
	_value = to_string(num);
}

BigInt::BigInt(const std::string& num) {
	string magnitude;
	if (num[0] == '+' or num[0] == '-') { // check for sign
		magnitude = num.substr(1);
	} else { // if no sign is specified
		magnitude = num;
	}

	if (is_valid_number(magnitude)) {
		_value = magnitude;
	} else {
		throw std::invalid_argument("Expected an integer, got \'" + num + "\'");
	}
}

// Relational operators:
bool BigInt::operator<(const BigInt& num) const {
	if (_value.length() == num._value.length())
		return _value < num._value;
	else
		return _value.length() < num._value.length();
}

bool BigInt::operator>(const BigInt& num) const {
	return !((*this < num) or (*this == num));
}

bool BigInt::operator<=(const BigInt& num) const {
	return (*this < num) or (*this == num);
}

bool BigInt::operator>=(const BigInt& num) const {
	return !(*this < num);
}

bool BigInt::operator==(const BigInt& num) const {
	return _value == num.get_value();
}

bool BigInt::operator==(const uint64_t num) const {
	return *this == BigInt(num);
}

bool BigInt::operator==(const string& num) const {
	return *this == BigInt(num);
}

// Binary arithmetic operators:
BigInt BigInt::operator+(const BigInt& num) const {
	// identify the numbers as `larger` and `smaller`
	string larger, smaller;
	tie(larger, smaller) = get_larger_and_smaller(_value, num.get_value());

	BigInt result{""}; // the resultant sum and the value is cleared as the digits will be appended
	short  carry{0};

	// add the two values
	for (long i = larger.size() - 1; i >= 0; i--) { //Warning co stím -> inicializování: Převod z: size_t na: long, může dojít ke ztrátě dat.MSVC(C4267)
		short int sum{0};
		sum           = larger[i] - '0' + smaller[i] - '0' + carry;
		result._value = to_string(sum % 10) + result._value;
		carry         = sum / (short int) 10;
	}
	if (carry) {
		result._value = to_string(carry) + result._value;
	}

	return result;
}

BigInt BigInt::operator-(const BigInt& num) const {
	// identify the numbers as `larger` and `smaller`
	string larger, smaller;
	tie(larger, smaller) = get_larger_and_smaller(_value, num.get_value());

	BigInt result{""};

	add_leading_zeroes(smaller, larger.size() - smaller.size());

	short difference{0};
	long  i, j;

	// subtract the two values
	for (i = larger.size() - 1; i >= 0; i--) {
		difference = larger[i] - smaller[i];

		if (difference < 0) {
			for (j = i - 1; j >= 0; j--) {
				if (larger[j] != '0') {
					larger[j]--; // borrow from the j-th digit
					break;
				}
			}
			j++;

			while (j != i) {
				larger[j] = '9'; // add the borrow and take away 1
				j++;
			}
			difference += 10; // add the borrow
		}
		result._value = to_string(difference) + result._value;
	}
	strip_leading_zeroes(result._value);

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
	tie(larger, smaller) = get_larger_and_smaller(_value, num._value);

	strip_leading_zeroes(smaller);

	BigInt    result{""}; // the resultant multipication and the value is cleared as the digits will be appended
	short int carry{0};

	for (long i = smaller.size() - 1; i >= 0; i--) { //Warning co stím -> inicializování: Převod z: size_t na: long, může dojít ke ztrátě dat.MSVC(C4267)
		BigInt temp{""};
		size_t step{smaller.size() - 1 - i};

		for (auto k = 0; k < step; k++) {
			temp._value = to_string(0) + temp._value;
		}

		for (long ii = larger.size() - 1; ii >= 0; ii--) { //Warning co stím -> inicializování: Převod z: size_t na: long, může dojít ke ztrátě dat.MSVC(C4267)
			short int mul{0};
			mul         = (larger[ii] - '0') * (smaller[i] - '0') + carry;
			temp._value = to_string(mul % 10) + temp._value;
			carry       = mul / (short int) 10;
		}

		if (carry) {
			temp._value = to_string(carry) + temp._value;
		}

		result = result + temp;
	}
	return result;
}

BigInt BigInt::operator/(const BigInt& num) const {
	if (num == 0) {
		throw logic_error("Attempted division by zero");
	}
	if (num == *this) {
		return BigInt(1);
	}
	if (num == 1) {
		return *this;
	}

	BigInt quotient{""};

	if (*this <= ULLONG_MAX and num <= ULLONG_MAX) {
		quotient = stoull(_value) / stoull(num.get_value());
	} else {
		BigInt temp, temp_quotient, temp_remainder;
		size_t temp_index = 0;

		temp_remainder._value = _value.substr(temp_index, num._value.size() - 1);
		temp_index            = num._value.size() - 1;

		while (temp_index < _value.size()) {
			temp._value = temp_remainder._value.append(1, _value[temp_index]);
			temp_index++;

			while (temp < num) {
				quotient._value = quotient._value + "0";

				if (temp_index < _value.size()) {
					temp._value.append(1, _value[temp_index]);
					temp_index++;
				} else {
					break;
				}
			}

			if (temp == num) {
				quotient._value = quotient._value + "1";
				temp_remainder  = 0;
			} else if (temp > num) {
				strip_leading_zeroes(temp._value);
				tie(temp_quotient, temp_remainder) = divide(temp, num);
				quotient._value += temp_quotient._value;
			}
		}
	}
	strip_leading_zeroes(quotient._value);

	return quotient;
}

BigInt BigInt::operator%(const BigInt& num) const {
	if (num == 0) {
		throw logic_error("Attempted division by zero");
	}
	if (num == 1 or num == *this) {
		return BigInt{0};
	}

	BigInt remainder{};

	if (*this <= ULLONG_MAX and num <= ULLONG_MAX) {
		remainder = stoull(_value) % stoull(num.get_value());
	} else {
		BigInt quotient = *this / num;
		remainder       = *this - quotient * num;
	}

	strip_leading_zeroes(remainder._value);

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

BigInt BigInt::operator-(const int& num) const {
	BigInt temp{to_string(num)};

	return *this - temp;
}

BigInt BigInt::operator/(const int& num) const {
	BigInt result{""};

	size_t size = (_value.size());

	if (size < 2) {
		result = to_string(stoll(_value) / 2);
	}

	for (long i = size - 2; i >= 0; i--) {
		long long int temp = stoll(_value.substr(i, 2));

		if (i == 0) {
			result._value = result._value + reverse_string(to_string(temp / 2));
		} else {
			result._value.push_back(((temp / 2) % 10) + '0');
		}
	}

	return reverse_string(result._value);
}

// iostream
ostream& operator<<(std::ostream& os, const BigInt& num) {
	os << num.get_value();
	return os;
}
