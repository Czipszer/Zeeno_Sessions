#include "Subtraction.hpp"
#include <numeric>

bool Subtraction::canProcess(const std::string& symbol) const {
	return symbol == "-" || symbol == "minus";
}

std::string Subtraction::preferredSymbol() const {
	return "-";
}

double Subtraction::compute(const std::vector<double>& operands) const {
	return std::accumulate(operands.cbegin() + 1, operands.cend(), *operands.begin(), std::minus<double>{});
}
