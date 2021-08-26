#pragma once
#ifndef _ZEENO_SUBTRACTION_HPP_
#	define _ZEENO_SUBTRACTION_HPP_

#	include "MathOperation.hpp"

class Subtraction final : public MathOperation {
public:
	bool        canProcess(const std::string& symbol) const override;
	double      compute(const std::vector<double>& operands) const override;
	std::string preferredSymbol() const override;
};

#endif
