#pragma once
#ifndef CHIP_GAUGE_HPP
#	define CHIP_GAUGE_HPP

#	include <string>

#	include "metric.hpp"

class Gauge : public Metric {
protected:
	double _value{0};

public:
	Gauge() = default;
	Gauge(std::string);
	Gauge(std::string, std::unordered_map<std::string, std::string>);
	Gauge(std::string, std::unordered_map<std::string, std::string>, double);

	void   resetValue();
	void   setValue(double);
	double getValue() const;
	double incValue();
	double decValue();

	std::string getInfo() const override;

	Gauge& operator++();
	Gauge& operator--();
	Gauge& operator=(double);
};

#endif