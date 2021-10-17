#pragma once
#ifndef CHIP_COUNTER_HPP
#	define CHIP_COUNTER_HPP

#	include <string>

#	include "metric.hpp"

class Counter : public Metric {
private:
	int _value{0};

public:
	Counter() = default;
	Counter(std::string);
	Counter(std::string, std::unordered_map<std::string, std::string>);
	Counter(std::string, std::unordered_map<std::string, std::string>, int);

	void resetValue();
	void setValue(int);
	int  getValue();
	int  incValue();

	std::string getInfo() const override;

	Counter& operator++();
	Counter& operator=(int);
};

#endif