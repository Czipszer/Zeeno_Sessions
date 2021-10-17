#include <fstream>
#include <sstream>
#include <string>

#include "counter.hpp"
#include "histogram.hpp"
#include "metric.hpp"

using namespace std;

Histogram::Histogram(string newName) : Metric(newName){};
Histogram::Histogram(string newName, unordered_map<string, string> newLabels) : Metric(newName, newLabels){};
Histogram::Histogram(string newName, unordered_map<string, string> newLabels, vector<double> newBucket) : Metric(newName, newLabels) {
	for (auto bucketLeght : newBucket) {
		auto         bucketLabels{newLabels};
		stringstream roundedNum;
		roundedNum << setprecision(5) << bucketLeght;
		bucketLabels["le"] = roundedNum.str();

		Counter bucket(newName + "_bucket", bucketLabels);

		_bucket.push_back(bucket);
	}

	auto infLabels{newLabels};
	infLabels["le"] = "+Inf";
	Counter infBucket(newName + "_bucket", infLabels);
	_bucket.push_back(infBucket);

	Counter sum(newName + "_sum", newLabels);
	_sum = sum;

	Counter count(newName + "_count", newLabels);
	_count = count;
};

void Histogram::resetValue() {
	for (auto sizeBucket : _bucket) {
		sizeBucket.resetValue();
	}

	_count.resetValue();
	_sum.resetValue();
}

string Histogram::getInfo() const {
	string info;
	for (auto sizeBucket : _bucket) {
		info += sizeBucket.getInfo() + "\n";
	}

	info += _count.getInfo() + "\n";
	info += _sum.getInfo() + "\n";

	auto epoch = chrono::time_point_cast<chrono::milliseconds>(_timestamp).time_since_epoch().count();
	if (epoch > 0) {
		info += _name + "_created " + to_string(epoch) + "\n";
	}

	return info;
}