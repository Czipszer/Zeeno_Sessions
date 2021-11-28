#include <fstream>
#include <sstream>
#include <string>

#include "metric.hpp"

using namespace std;

Metric::Metric(string newName, std::unordered_map<std::string, std::string> newLabels) {
	//name
	_name = newName;

	//labels
	_labels = newLabels;

	//time stamp
	_timestamp = Clock::now();
};

void Metric::setUnit(string newUnit) {
	_unit = newUnit;
}

void Metric::setHelp(string newHelp) {
	_help = newHelp;
}

string Metric::getHead() const {
	std::stringstream info;

	info << "# TYPE " << getFullName() << " " << getType() << std::endl;

	if (!_unit.empty()) {
		info << "# UNIT " << getFullName() << " " << getUnit() << std::endl;
	}

	if (!_help.empty()) {
		info << "# HELP " << getFullName() << " " << getHelp() << std::endl;
	}

	return info.str();
}

string Metric::getUnit() const {
	return _unit;
}

string Metric::getHelp() const {
	return _help;
}

string Metric::getName() const {
	return _name;
}

string Metric::getFullName() const {
	string info;

	if (_unit.empty()) {
		info = _name;
	} else {
		info = _name + "_" + getUnit();
	}

	return info;
}

unordered_map<string, string> Metric::getLabels() const {
	return _labels;
}

Metric::Clock::time_point Metric::getTimestamp() const {
	return _timestamp;
}