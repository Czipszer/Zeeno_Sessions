#include <fstream>
#include <string>

#include "gauge.hpp"

using namespace std;

Gauge::Gauge(string newName) : Counter(newName){};
Gauge::Gauge(string newName, unordered_map<string, string> newLabels) : Counter(newName, newLabels){};
Gauge::Gauge(string newName, unordered_map<string, string> newLabels, int newValue) : Counter(newName, newLabels) {
	_value = newValue;
};

int Gauge::decValue() {
	return _value--;
};

Gauge& Gauge::operator--() {
	_value--;
	return *this;
}
