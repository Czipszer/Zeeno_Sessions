#pragma once
#ifndef CHIP_COUNTER_HPP
#	define CHIP_COUNTER_HPP

#	include <string>

#	include "metric.hpp"

class Counter : public Metric {
public:
	Counter() = default;
	Counter(std::string name, std::vector<std::pair<std::string, std::string>> labels = {}, int value = 0);

	void resetValue();
	void setValue(int newValue);
	int  getValue() const;
	int  incValue();

	void makeChange(std::string value) override;

	std::string getInfo() const override;

	std::string getType() const override;

	Counter& operator++();
	Counter& operator=(int);

protected:
	int _value{0};
};

#endif