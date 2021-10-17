#include <fstream>
#include <sstream>
#include <string>


#include "gauge.hpp"

using namespace std;

Gauge::Gauge(string newName) : Metric(newName){};
Gauge::Gauge(string newName, unordered_map<string, string> newLabels) : Metric(newName, newLabels){};
Gauge::Gauge(string newName, unordered_map<string, string> newLabels, double newValue) : Metric(newName, newLabels) {
	_value = newValue;
};

void Gauge::resetValue() {
	_value = 0;
}

void Gauge::setValue(double newValue) {
	_value = newValue;
}

double Gauge::getValue() const {
	return _value;
}

double Gauge::incValue() {
	return _value++;
}

double Gauge::decValue() {
	return _value--;
}

string Gauge::getInfo() const {
	string info{_name};

	size_t sizeLabels{_labels.size()};
	if (sizeLabels != 0) {
		string tempInfo = "{";
		size_t i{0};

		for (auto [key, value] : _labels) {
			tempInfo = tempInfo + key + "=\"" + value + "\"";
			i++;

			if (sizeLabels != 1 && i != sizeLabels) {
				tempInfo = tempInfo + ",";
			}
		}
		info = info + tempInfo + "}";
	}

	stringstream roundedNum;
	roundedNum << setprecision(6) << _value;
	info = info + " " + roundedNum.str();

	auto epoch = chrono::time_point_cast<chrono::milliseconds>(_timestamp).time_since_epoch().count();
	if (epoch > 0) {
		info = info + " " + to_string(epoch);
	}

	return info;
}

Gauge& Gauge::operator++() {
	_value++;
	return *this;
}

Gauge& Gauge::operator--() {
	_value--;
	return *this;
}

Gauge& Gauge::operator=(double newValue) {
	_value = newValue;
	return *this;
}