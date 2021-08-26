#include "MathOperation.hpp"

bool MathOperation::canProcess(const std::string& symbol) const {
	return symbol == preferredSymbol();
}
size_t MathOperation::minOperands() const {
	return 1;
}

size_t MathOperation::maxOperands() const {
	return 10;
}