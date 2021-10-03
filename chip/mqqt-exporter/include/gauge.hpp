#pragma once
#ifndef CHIP_GAUGE_HPP
#	define CHIP_GAUGE_HPP

#	include <string>

#	include "metric.hpp"

class Gauge : public Metric {
private:
	int _value;

public:
	Gauge(std::string);
	Gauge(std::string, std::unordered_multimap<std::string, std::string>);
	Gauge(std::string, std::unordered_multimap<std::string, std::string>, int);

	void resetValue();
	void setValue(int);
	int  getValue();
	int  incValue();
	int  decValue();

	std::string getInfo() const override;

	Gauge& operator++();
	Gauge& operator--();
	Gauge& operator=(int);
};

#endif