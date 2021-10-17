#pragma once
#ifndef CHIP_GAUGE_HPP
#	define CHIP_GAUGE_HPP

#	include <string>

#	include "counter.hpp"

class Gauge : public Counter {
private:
	int _value{0};

public:
	Gauge() = default;
	Gauge(std::string);
	Gauge(std::string, std::unordered_map<std::string, std::string>);
	Gauge(std::string, std::unordered_map<std::string, std::string>, int);

	int decValue();

	Gauge& operator--();
};

#endif