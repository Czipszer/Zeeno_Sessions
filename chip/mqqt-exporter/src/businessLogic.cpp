#include <cstdlib>
#include <iostream>
#include <ranges>
#include <regex>
#include <string>
#include <vector>

#include "businessLogic.hpp"
#include "configReader.hpp"
#include "counter.hpp"
#include "gauge.hpp"
#include "histogram.hpp"
#include "metric.hpp"
#include "myException.hpp"
#include "summary.hpp"

using namespace std;

BusinessLogic::BusinessLogic(const vector<MetricsData>& newDataSets) {
	_metrics  = make_shared<Metrics>();
	_dataSets = newDataSets;
}

shared_ptr<Metrics> BusinessLogic::getMetrics() {
	return _metrics;
}

void BusinessLogic::processMessage(const string& topic, const string& value) {
	for (auto dataSet : _dataSets) {
		string charWanted{"#+"};
		string regexQuery{dataSet.topic};

		size_t charPosition = regexQuery.find_first_of(charWanted);

		while (charPosition != string::npos) {
			string regexReplacement;

			if (dataSet.topic[charPosition] == '+') {
				regexReplacement = "([^/]+)";
			}

			if (dataSet.topic[charPosition] == '#') {
				regexReplacement = ".*";
			}

			regexQuery   = dataSet.topic.substr(0, charPosition) + regexReplacement + dataSet.topic.substr(charPosition + 1);
			charPosition = regexQuery.find_first_of(charWanted, charPosition + regexReplacement.size());
		}

		regex  regexWanted{regexQuery};
		smatch regexMatch;

		if (regex_match(topic, regexMatch, regexWanted)) {
			for (auto& value : dataSet.labels | views::values) {
				if (value == "@value") {
					value = regexMatch[1].str();
				}
			}

			bool metricExist{false};
			{
				scoped_lock lock{_metrics->mutex};

				for (auto& metric : _metrics->metrics) {
					if (dataSet.name == metric->getName() && dataSet.labels == metric->getLabels()) {
						metric->makeChange(value);
						metricExist = true;
						break;
					}
				}
			}

			if (!metricExist) {
				createMetric(dataSet, stod(value));

				metricExist = false;
			}
		}
	}
}

void BusinessLogic::createMetric(const MetricsData& dataSet, const double& value) {
	if (dataSet.type == "counter") {
		auto newMetric = make_shared<Counter>(dataSet.name, dataSet.labels, static_cast<int>((value)));

		newMetric->setHelp(dataSet.help);
		newMetric->setUnit(dataSet.unit);
		newMetric->enableTimestamp(dataSet.timestemp);

		scoped_lock lock{_metrics->mutex};

		_metrics->metrics.push_back(newMetric);
	}

	if (dataSet.type == "gauge") {
		auto newMetric = make_shared<Gauge>(dataSet.name, dataSet.labels, value);

		newMetric->setHelp(dataSet.help);
		newMetric->setUnit(dataSet.unit);
		newMetric->enableTimestamp(dataSet.timestemp);

		scoped_lock lock{_metrics->mutex};

		_metrics->metrics.push_back(newMetric);
	}

	if (dataSet.type == "summary") {
		auto newMetric = make_shared<Summary>(dataSet.name, dataSet.labels, dataSet.bucketsOrQuantiles);

		newMetric->addSample(value);

		newMetric->setHelp(dataSet.help);
		newMetric->setUnit(dataSet.unit);
		newMetric->enableTimestamp(dataSet.timestemp);

		scoped_lock lock{_metrics->mutex};

		_metrics->metrics.push_back(newMetric);
	}

	if (dataSet.type == "histogram") {
		auto newMetric = make_shared<Histogram>(dataSet.name, dataSet.labels, dataSet.bucketsOrQuantiles);

		newMetric->addSample(static_cast<int>((value)));

		newMetric->setHelp(dataSet.help);
		newMetric->setUnit(dataSet.unit);
		newMetric->enableTimestamp(dataSet.timestemp);

		scoped_lock lock{_metrics->mutex};

		_metrics->metrics.push_back(newMetric);
	}
}
