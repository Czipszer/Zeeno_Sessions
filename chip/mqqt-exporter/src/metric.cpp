#include <fstream>
#include <string>

#include "metric.hpp"

using namespace std;

Metric::Metric(string newName) {
	//name
	_name = newName;

	//time stamp
	_timestamp = (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
}

Metric::Metric(string newName, std::unordered_map<std::string, std::string> newLabels) {
	//name
	_name = newName;

	//labels
	_labels = newLabels;

	//time stamp
	_timestamp = (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());
};

string Metric::getName() const {
	return _name;
}

unordered_map<string, string> Metric::getLabels() const {
	return _labels;
}

int64_t Metric::getTimestamp() const {
	return _timestamp;
}