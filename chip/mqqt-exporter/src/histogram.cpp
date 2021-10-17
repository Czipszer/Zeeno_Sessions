#include <fstream>
#include <limits>
#include <sstream>
#include <string>

#include "counter.hpp"
#include "histogram.hpp"
#include "metric.hpp"

using namespace std;

Histogram::Histogram(string newName) : Metric(newName){};
Histogram::Histogram(string newName, unordered_map<string, string> newLabels) : Metric(newName, newLabels){};
Histogram::Histogram(string newName, unordered_map<string, string> newLabels, vector<double> newBucket) : Metric(newName, newLabels) {
	for (auto bucketLenght : newBucket) {
		auto         bucketLabels{newLabels};
		stringstream roundedNum;
		roundedNum << setprecision(5) << bucketLenght;
		bucketLabels["le"] = roundedNum.str();

		Counter bucket(newName + "_bucket", bucketLabels);

		_bucket.push_back(make_pair(bucketLenght, bucket));
	}

	auto infLabels{newLabels};
	infLabels["le"] = "+Inf";
	Counter infBucket(newName + "_bucket", infLabels);
	_bucket.push_back(make_pair(numeric_limits<double>::infinity(), infBucket));

	Counter sum(newName + "_sum", newLabels);
	_sum = sum;

	Counter count(newName + "_count", newLabels);
	_count = count;
};

void Histogram::resetValue() {
	for (auto& [le, counter] : _bucket) {
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
	for (auto& [le, counter] : _bucket) {
		info += counter.getInfo() + "\n";
	}

	info += _count.getInfo() + "\n";
	info += _sum.getInfo() + "\n";

	auto epoch = chrono::time_point_cast<chrono::milliseconds>(_timestamp).time_since_epoch().count();
	if (epoch > 0) {
		info += _name + "_created " + to_string(epoch) + "\n";
	}

	return info;
}