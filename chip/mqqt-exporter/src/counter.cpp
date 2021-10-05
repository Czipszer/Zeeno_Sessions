#include <fstream>
#include <string>

#include "counter.hpp"

using namespace std;

Counter::Counter(string newName) : Metric(newName){};
Counter::Counter(string newName, unordered_map<string, string> newLabels) : Metric(newName, newLabels){};
Counter::Counter(string newName, unordered_map<string, string> newLabels, int newValue) : Metric(newName, newLabels) {
	_value = newValue;
};

void Counter::resetValue() {
	_value = 0;
}

void Counter::setValue(int newValue) {
	_value = newValue;
}

int Counter::getValue() {
	return _value;
}

int Counter::incValue() {
	return _value++;
};

string Counter::getInfo() const {
	string info{_name};

	size_t sizeLabels{_labels.size()};
	if (sizeLabels != 0) {
		string tempInfo = "{";
		size_t i{0};

		for (auto x : _labels) {
			tempInfo = tempInfo + x.first + "=\"" + x.second + "\"";
			i++;

			if (sizeLabels != 1 && i != sizeLabels) {
				tempInfo = tempInfo + ",";
			}
		}
		info = info + tempInfo + "}";
	}

	info = info + " " + to_string(_value);

	if (_timestamp != 0) {
		info = info + " " + to_string(_timestamp);
	}

	return info;
}

Counter& Counter::operator++() {
	_value++;
	return *this;
}

Counter& Counter::operator=(int newValue) {
	_value = newValue;
	return *this;
}