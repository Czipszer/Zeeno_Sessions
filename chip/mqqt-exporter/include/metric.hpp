#pragma once
#ifndef CHIP_METRIC_HPP
#	define CHIP_METRIC_HPP

#	include <string>
#	include <unordered_map>
#	include <chrono>

class Metric {
protected:
	std::string                                  _name;
	std::unordered_map<std::string, std::string> _labels;
	int64_t                                      _timestamp{};

public:
	Metric() = default;
	Metric(std::string);
	Metric(std::string, std::unordered_map<std::string, std::string>);

	virtual ~Metric() = default;

	virtual std::string getInfo() const = 0;

	std::string                                  getName() const;
	std::unordered_map<std::string, std::string> getLabels() const;
	int64_t                                      getTimestamp() const;
};

#endif