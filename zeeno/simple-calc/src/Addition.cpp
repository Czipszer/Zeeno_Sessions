#include "Addition.hpp"
#include <numeric>

bool Addition::canProcess(const std::string& symbol) const {
	return symbol == "+" || symbol == "sum";
}

std::string Addition::preferredSymbol() const {
	return "+";
}

double Addition::compute(const std::vector<double>& operands) const {
	return std::accumulate(operands.cbegin(), operands.cend(), 0.0);
}
