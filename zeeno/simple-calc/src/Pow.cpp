#include "Pow.hpp"
#include <cmath>

std::string Pow::preferredSymbol() const {
	return "pow";
}

size_t Pow::maxOperands() const {
	return 2;
}

size_t Pow::minOperands() const {
	return 2;
}

double Pow::compute(const std::vector<double>& operands) const {
	return std::pow(operands.at(0), operands.at(1));
}
