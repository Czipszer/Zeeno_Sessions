#include <iomanip>
#include <limits>
#include <ranges>
#include <sstream>
#include <string>

#include "counter.hpp"
#include "histogram.hpp"
#include "metric.hpp"

using namespace std;

Histogram::Histogram(string newName, unordered_map<string, string> newLabels, vector<double> newBucket) : Metric(newName, newLabels) {
	_type = "historgram";

	for (auto bucketLenght : newBucket) {
		auto         bucketLabels{newLabels};
		stringstream roundedNum;
		roundedNum << setprecision(5) << bucketLenght;
		bucketLabels["le"] = roundedNum.str();

		Counter bucket(newName, bucketLabels);
		bucket.setPrefix("bucket");

		_bucket.push_back(make_pair(bucketLenght, bucket));
	}

	auto infLabels{newLabels};
	infLabels["le"] = "+Inf";
	Counter infBucket(newName, infLabels);
	infBucket.setPrefix("bucket");
	_bucket.push_back(make_pair(numeric_limits<double>::infinity(), infBucket));

	Counter sum(newName, newLabels);
	_sum = sum;
	_sum.setPrefix("sum");

	Counter count(newName, newLabels);
	_count = count;
	_count.setPrefix("count");
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

void Histogram::addSample(double typeBucket) {
	for (auto& [le, counter] : _bucket) {
		if (le >= typeBucket) {
			_count.incValue();
			counter.incValue();
			break;
		}
	}

	int sum{0};
	for (auto& [le, counter] : _bucket) {
		sum += counter.getValue();
	}
	_sum.setValue(sum);
}

string Histogram::getInfo() const {
	string info;
	for (auto& counter : _bucket | views::values) {
		info += counter.getInfo() + "\n";
	}

	info += _count.getInfo() + "\n";
	info += _sum.getInfo() + "\n";

	auto epoch = chrono::time_point_cast<chrono::milliseconds>(_timestamp).time_since_epoch().count();
	if (epoch > 0) {
		info += getFullName() + "_created " + to_string(epoch);
	}

	return info;
}

string Histogram::getType() const {
	return _type;
}