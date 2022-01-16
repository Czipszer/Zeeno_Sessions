#pragma once
#ifndef CHIP_BUSINESS_LOGIC_HPP
#	define CHIP_BUSINESS_LOGIC_HPP

#	include <cstdlib>
#	include <iostream>
#	include <vector>

#	include "metric.hpp"
#	include "configReader.hpp"

class BusinessLogic {
public:
	BusinessLogic(const std::vector<MetricsData>& dataSets);

	std::shared_ptr<std::vector<std::shared_ptr<Metric>>> getMetrics();

	void processMessage(const std::string& topic, const std::string& value);

private:
	std::shared_ptr<std::vector<std::shared_ptr<Metric>>> _metrics;
	std::vector<MetricsData>                              _dataSets;

	void createMetric(const MetricsData& singleMetricData, const double& value);
};
#endif