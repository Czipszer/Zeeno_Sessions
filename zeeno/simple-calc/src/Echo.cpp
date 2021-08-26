#include "Echo.hpp"
#include <cmath>

std::string Echo::preferredSymbol() const {
	return "echo";
}

size_t Echo::maxOperands() const {
	return 1;
}

double Echo::compute(const std::vector<double>& operands) const {
	return operands.at(0);
}

bool Echo::canProcess(const std::string&) const {
	return true;
}
