#pragma once
#ifndef CHIP_HISTOGRAM_HPP
#	define CHIP_HISTOGRAM_HPP

#	include <string>
#	include <vector>

#	include "metric.hpp"
#	include "counter.hpp"

class Histogram : public Metric {
public:
	Histogram() = default;
	Histogram(std::string name, std::unordered_map<std::string, std::string> labels = {}, std::vector<double> bucket = {});

	void setUnit(std::string unit) override;

	void resetValue();
	void addSample(double);

	std::string getInfo() const override;
	std::string getType() const override;

private:
	std::vector<std::pair<double, Counter>> _bucket;
	Counter                                 _sum;
	Counter                                 _count;
};

#endif