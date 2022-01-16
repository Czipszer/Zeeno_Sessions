#include <string>

#include "counter.hpp"

using namespace std;

Counter::Counter(string newName, vector<pair<string, string>> newLabels, int newValue) : Metric(newName, newLabels), _value{newValue} {
	_type = "counter";
}

void Counter::resetValue() {
	_value = 0;
}

void Counter::setValue(int newValue) {
	_value = newValue;
}

int Counter::getValue() const {
	return _value;
}

int Counter::incValue() {
	return ++_value;
}

void Counter::makeChange(std::string stringValue) {
	int newValue{stoi(stringValue)};

	if ((newValue - _value) > 0) {
		setValue(newValue);
	}
}

string Counter::getInfo() const {
	string info{getFullName()};

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

	info = info + " " + to_string(_value);

	if (_timestampState) {
		auto epoch = chrono::time_point_cast<chrono::milliseconds>(_timestamp).time_since_epoch().count();
		if (epoch > 0) {
			info = info + " " + to_string(epoch);
		}
	}

	return info;
}

string Counter::getType() const {
	return _type;
}

Counter& Counter::operator++() {
	_value++;
	return *this;
}

Counter& Counter::operator=(int newValue) {
	_value = newValue;
	return *this;
}