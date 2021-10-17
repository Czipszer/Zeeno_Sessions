#pragma once
#ifndef CHIP_HISTOGRAM_HPP
#	define CHIP_HISTOGRAM_HPP

#	include <string>
#	include <vector>

#	include "metric.hpp"
#	include "counter.hpp"

class Histogram : public Metric {
private:
	std::vector<Counter> _bucket;
	Counter              _sum;
	Counter              _count;

public:
	Histogram(std::string);
	Histogram(std::string, std::unordered_map<std::string, std::string>);
	Histogram(std::string, std::unordered_map<std::string, std::string>, std::vector<double>);

	void resetValue();

	std::string getInfo() const override;
};

#endif