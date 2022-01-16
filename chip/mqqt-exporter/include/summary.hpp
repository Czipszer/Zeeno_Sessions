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
	    std::string                                      name,
	    std::vector<std::pair<std::string, std::string>> labels       = {},
	    std::vector<double>                              quantiles    = {},
	    std::chrono::minutes                             windowPeriod = std::chrono::minutes(5));

	void setUnit(std::string unit) override;

	void enableTimestamp(bool state) override;

	void resetValue();
	void addSample(double);

	void makeChange(std::string value) override;

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