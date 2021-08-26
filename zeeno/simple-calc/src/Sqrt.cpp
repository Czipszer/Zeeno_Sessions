#include "Sqrt.hpp"
#include <cmath>

std::string Sqrt::preferredSymbol() const {
	return "sqrt";
}

size_t Sqrt::maxOperands() const {
	return 1;
}

double Sqrt::compute(const std::vector<double>& operands) const {
	return std::sqrt(*operands.begin());
}
