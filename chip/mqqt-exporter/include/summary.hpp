#pragma once
#ifndef CHIP_SUMMARY_HPP
#	define CHIP_SUMMARY_HPP

#	include <string>
#	include <vector>
#	include <deque>

#	include "metric.hpp"
#	include "counter.hpp"
#	include "gauge.hpp"

class Summary : public Metric {
public:
	Summary(
	    std::string                                  name,
	    std::unordered_map<std::string, std::string> labels       = {},
	    std::vector<double>                          quantiles    = {},
	    std::chrono::minutes                         windowPeriod = std::chrono::minutes(5));

	void resetValue();
	void addSample(double);

	std::string getInfo() const override;

	std::string getType() const override;

private:
	std::vector<std::pair<double, Gauge>> _quantiles;
	Gauge                                 _sum;
	Counter                               _count;

	std::deque<std::pair<double, Clock::time_point>> _queue;
	std::chrono::milliseconds                        _windowPeriod{std::chrono::minutes(5)};
};

#endif