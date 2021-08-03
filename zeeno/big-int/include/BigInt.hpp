#pragma once
#ifndef ZEENO_BIG_INT_HPP
#	define ZEENO_BIG_INT_HPP

/**
 * We separate declarations and definitions of the class.
 * Here are only things important to know when using the class,
 * all the details are hidden in the *.cpp file
*/

#	include <iostream>
#	include <string_view>
#	include <vector>
#	include <cstdint>
#	include <limits>

class BigInt {
public:
	enum class Base { Hex };
	/*
	Constructors are important functions. They are called when you initialize the class.
	So if you write
	{
		BigInt a{};
	}
	then the first constructor is called and if you write
	{
		BigInt a{123456};
	}
	then the second constructor is called.
	*/
	BigInt() = default;
	BigInt(std::string_view, Base);

	/**
 	  * Allow addition of two BigInt
	  */
	BigInt operator+(BigInt other);

	/**
	  * Allow to make a string out of the number
	  */
	std::string to_string(Base) const;

	BigInt& normalize();

private:
	using Type                         = std::uint64_t;
	static constexpr size_t bytes      = sizeof(Type);
	static constexpr Type   max        = std::numeric_limits<Type>::max();
	static constexpr Type   highNibble = max - (max >> 4);

	std::vector<Type> _data; //This store data in the reverse order, so the number 123 is stored as [3, 2, 1]
};

// This will allow to use BigInt in "std::cout <<"
std::ostream& operator<<(std::ostream& os, const BigInt& big);

#endif
