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
private:
	using Clock = std::chrono::system_clock;

	std::vector<std::pair<double, Gauge>> _quantiles;
	Gauge                                 _sum;
	Counter                               _count;

	std::deque<std::pair<double, Clock::time_point>> _queue;
	std::chrono::milliseconds                        _windowPeriod{std::chrono::minutes(5)};

public:
	Summary(std::string);
	Summary(std::string, std::unordered_map<std::string, std::string>);
	Summary(std::string, std::unordered_map<std::string, std::string>, std::vector<double>, std::chrono::minutes);

	void resetValue();
	void addSample(double);

	std::string getInfo() const override;
};

#endif