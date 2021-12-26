#include <algorithm>
#include <fstream>
#include <iomanip>
#include <ranges>
#include <sstream>
#include <string>

#include "counter.hpp"
#include "metric.hpp"
#include "summary.hpp"

using namespace std;
using namespace std::chrono_literals;

Summary::Summary(string newName, vector<pair<string, string>> newLabels, vector<double> newQuantiles, chrono::minutes newWindowPeriod)
    : Metric(newName, newLabels) {
	_type = "summary";

	for (auto quantilesLenght : newQuantiles) {
		auto         quantilesLabels{newLabels};
		stringstream roundedNum;
		roundedNum << setprecision(4) << quantilesLenght;
		quantilesLabels.push_back(make_pair("quantile", roundedNum.str()));

		Gauge quantile(newName, quantilesLabels);

		_quantiles.push_back(make_pair(quantilesLenght, quantile));
	}

	Gauge sum(newName, newLabels);
	_sum = sum;
	_sum.setPrefix("sum");

	Counter count(newName, newLabels);
	_count = count;
	_count.setPrefix("count");

	_windowPeriod = newWindowPeriod;
}

void Summary::setUnit(string newUnit) {
	Metric::setUnit(newUnit);

	_count.setUnit(newUnit);
	_sum.setUnit(newUnit);

	for (auto& gauge : _quantiles | views::values) {
		gauge.setUnit(newUnit);
	}
}

void Summary::resetValue() {
	for (auto& [quantile, gauge] : _quantiles) {
		gauge.resetValue();
	}

	_count.resetValue();
	_sum.resetValue();
}

void Summary::addSample(double sampleQuantile) {
	_queue.push_back(make_pair(sampleQuantile, Clock::now()));

	while ((_queue.front().second) < (Clock::now() - _windowPeriod)) {
		_queue.pop_front();
	}
}

void Summary::makeChange(std::string stringValue) {
	double newValue{stod(stringValue)};

	addSample(newValue);
}

string Summary::getInfo() const {
	string info;

	auto view = _queue | views::filter([this](std::pair<double, Clock::time_point> p) { return p.second >= (Clock::now() - _windowPeriod); }) | views::keys;
	vector<double> values{view.begin(), view.end()};
	ranges::sort(values);

	auto quantiles = _quantiles;
	for (auto& [quantile, gauge] : quantiles) {
		double temp{};
		int    roundedTemp{};
		temp        = floor(values.size() * quantile);
		roundedTemp = static_cast<int>(temp);

		if (!values.empty()) {
			gauge.setValue(values[roundedTemp]);
		}
		info += gauge.getInfo() + "\n";
	}

	double sumSummary{0};
	auto   sum   = _sum;
	auto   count = _count;
	for (auto value : values) {
		count.incValue();
		sumSummary += value;
	}
	info += count.getInfo() + "\n";

	sum.setValue(sumSummary);
	info += sum.getInfo() + "\n";

	auto epoch = chrono::time_point_cast<chrono::milliseconds>(_timestamp).time_since_epoch().count();
	if (epoch > 0) {
		info += getFullName() + "_created " + to_string(epoch);
	}

	return info;
}

string Summary::getType() const {
	return _type;
}