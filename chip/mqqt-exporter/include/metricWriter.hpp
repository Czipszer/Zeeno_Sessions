#pragma once
#ifndef CHIP_METRICWRITER_HPP
#	define CHIP_METRICWRITER_HPP

#	include <string>
#	include <memory>
#	include <chrono>
#	include <thread>
#	include <fstream>

#	include "metric.hpp"

class MetricWriter {
public:
	MetricWriter(
	    std::string nameFile, std::shared_ptr<std::vector<std::shared_ptr<Metric>>> metrics, std::chrono::seconds writePeriod = std::chrono::seconds(10));

	virtual ~MetricWriter();

	void periodicWrite();

	void finish();

private:
	std::string                                           _nameFile;
	std::shared_ptr<std::vector<std::shared_ptr<Metric>>> _metrics;
	std::chrono::seconds                                  _writePeriod;
	std::jthread                                          _worker;
	std::fstream                                          _file;
	static std::atomic_bool                               _terninate;
};

#endif