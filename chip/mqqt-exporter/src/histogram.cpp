#include <iomanip>
#include <limits>
#include <ranges>
#include <sstream>
#include <string>

#include "counter.hpp"
#include "histogram.hpp"
#include "metric.hpp"

using namespace std;
using namespace std::chrono_literals;

Histogram::Histogram(string newName, vector<pair<string, string>> newLabels, vector<double> newBucket, chrono::minutes newWindowPeriod)
    : Metric(newName, newLabels) {
	_type = "historgram";

	for (auto bucketLenght : newBucket) {
		auto         bucketLabels{newLabels};
		stringstream roundedNum;
		roundedNum << setprecision(4) << bucketLenght;
		bucketLabels.push_back(make_pair("le", roundedNum.str()));

		Counter bucket(newName, bucketLabels);
		bucket.setPrefix("bucket");

		_bucket.push_back(make_pair(bucketLenght, bucket));
	}

	auto infLabels{newLabels};
	infLabels.push_back(make_pair("le", "+Inf"));
	Counter infBucket(newName, infLabels);
	infBucket.setPrefix("bucket");
	_bucket.push_back(make_pair(numeric_limits<double>::infinity(), infBucket));

	Counter sum(newName, newLabels);
	_sum = sum;
	_sum.setPrefix("sum");

	Counter count(newName, newLabels);
	_count = count;
	_count.setPrefix("count");

	_windowPeriod = newWindowPeriod;
}

void Histogram::setUnit(string newUnit) {
	Metric::setUnit(newUnit);

	_count.setUnit(newUnit);
	_sum.setUnit(newUnit);

	for (auto& counter : _bucket | views::values) {
		counter.setUnit(newUnit);
	}
}

void Histogram::resetValue() {
	for (auto& counter : _bucket | views::values) {
		counter.resetValue();
	}

	_count.resetValue();
	_sum.resetValue();
}

void Histogram::addSample(double sampleBucket) {
	_sample.push_back(make_pair(sampleBucket, Clock::now()));

	while ((_sample.front().second) < (Clock::now() - _windowPeriod)) {
		_sample.pop_front();
	}
}

void Histogram::makeChange(std::string stringValue) {
	double newValue{stod(stringValue)};

	addSample(newValue);
}

string Histogram::getInfo() const {
	string info;

	auto view = _sample | views::filter([this](std::pair<double, Clock::time_point> p) { return p.second >= (Clock::now() - _windowPeriod); }) | views::keys;
	vector<double> values{view.begin(), view.end()};

	auto bucket = _bucket;
	auto count  = _count;
	for (auto value : values) {
		for (auto& [le, counter] : bucket) {
			if (le >= value) {
				count.incValue();
				counter.incValue();
				break;
			}
		}
	}
	for (auto& counter : bucket | views::values) {
		info += counter.getInfo() + "\n";
	}
	info += count.getInfo() + "\n";

	double tempSum{0};
	auto   sum = _sum;
	for (auto& value : values) {
		tempSum += value;
	}
	sum.setValue(static_cast<int>(tempSum));
	info += sum.getInfo() + "\n";

	auto epoch = chrono::time_point_cast<chrono::milliseconds>(_timestamp).time_since_epoch().count();
	if (epoch > 0) {
		info += getFullName() + "_created " + to_string(epoch);
	}

	return info;
}

string Histogram::getType() const {
	return _type;
}