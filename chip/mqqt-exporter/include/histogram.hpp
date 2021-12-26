#pragma once
#ifndef CHIP_HISTOGRAM_HPP
#	define CHIP_HISTOGRAM_HPP

#	include <string>
#	include <vector>
#	include <deque>

#	include "metric.hpp"
#	include "counter.hpp"

class Histogram : public Metric {
public:
	Histogram() = default;
	Histogram(
	    std::string                                      name,
	    std::vector<std::pair<std::string, std::string>> labels       = {},
	    std::vector<double>                              bucket       = {},
	    std::chrono::minutes                             windowPeriod = std::chrono::minutes(5));

	void setUnit(std::string unit) override;

	void resetValue();
	void addSample(double);

	void makeChange(std::string value) override;

	std::string getInfo() const override;
	std::string getType() const override;

private:
	std::vector<std::pair<double, Counter>> _bucket;
	Counter                                 _sum;
	Counter                                 _count;

	std::deque<std::pair<double, Clock::time_point>> _sample;
	std::chrono::milliseconds                        _windowPeriod{std::chrono::minutes(5)};
};

#endif