#pragma once
#ifndef CHIP_METRICWRITER_HPP
#	define CHIP_METRICWRITER_HPP

#	include <string>
#	include <memory>
#	include <chrono>
#	include <thread>
#	include <fstream>

#	include "businessLogic.hpp"
#	include "metric.hpp"

class MetricWriter {
public:
	MetricWriter(std::string nameFile, std::shared_ptr<Metrics> metrics, std::chrono::seconds writePeriod = std::chrono::seconds(10));

	virtual ~MetricWriter();

	void periodicWrite();

	void finish();

private:
	std::string              _nameFile;
	std::shared_ptr<Metrics> _metrics;
	std::chrono::seconds     _writePeriod;
	std::jthread             _worker;
	std::fstream             _file;
	static std::atomic_bool  _terninate;
};

#endif