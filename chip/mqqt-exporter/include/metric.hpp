#pragma once
#ifndef CHIP_METRIC_HPP
#	define CHIP_METRIC_HPP

#	include <string>
#	include <unordered_map>
#	include <chrono>

class Metric {
public:
	using Clock = std::chrono::system_clock;

	Metric() = default;
	Metric(std::string name, std::vector<std::pair<std::string, std::string>> labels = {});

	virtual ~Metric() = default;

	virtual void makeChange(std::string value) = 0;

	void         setName(std::string name);
	void         setPrefix(std::string prefix);
	virtual void setUnit(std::string unit);
	void         setHelp(std::string help);

	std::string         getHead() const;
	virtual std::string getInfo() const = 0;

	virtual std::string getType() const = 0;
	std::string         getUnit() const;
	std::string         getHelp() const;

	std::string                                      getName() const;
	std::string                                      getPrefix() const;
	std::string                                      getFullName() const;
	std::vector<std::pair<std::string, std::string>> getLabels() const;
	Clock::time_point                                getTimestamp() const;

protected:
	std::string _type;
	std::string _unit;
	std::string _help;

	std::string                                      _name;
	std::string                                      _prefix;
	std::vector<std::pair<std::string, std::string>> _labels;
	Clock::time_point                                _timestamp{};
};

#endif