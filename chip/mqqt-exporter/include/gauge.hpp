#pragma once
#ifndef CHIP_GAUGE_HPP
#	define CHIP_GAUGE_HPP

#	include <string>

#	include "metric.hpp"

class Gauge : public Metric {
public:
	Gauge() = default;
	Gauge(std::string name, std::unordered_map<std::string, std::string> labels = {}, double value = 0);

	void   resetValue();
	void   setValue(double);
	double getValue() const;
	double incValue();
	double decValue();

	std::string getInfo() const override;

	std::string getType() const override;

	Gauge& operator++();
	Gauge& operator--();
	Gauge& operator=(double);

protected:
	double _value{0};
};

#endif