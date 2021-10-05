#include <fstream>
#include <string>

#include "gauge.hpp"

using namespace std;

Gauge::Gauge(string newName) : Metric(newName){};
Gauge::Gauge(string newName, unordered_map<string, string> newLabels) : Metric(newName, newLabels){};
Gauge::Gauge(string newName, unordered_map<string, string> newLabels, int newValue) : Metric(newName, newLabels) {
	_value = newValue;
};

void Gauge::resetValue() {
	_value = 0;
}

void Gauge::setValue(int newValue) {
	_value = newValue;
}

int Gauge::getValue() {
	return _value;
}

int Gauge::incValue() {
	return _value++;
};

int Gauge::decValue() {
	return _value--;
};

string Gauge::getInfo() const {
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

Gauge& Gauge::operator++() {
	_value++;
	return *this;
}

Gauge& Gauge::operator--() {
	_value++;
	return *this;
}

Gauge& Gauge::operator=(int newValue) {
	_value = newValue;
	return *this;
}