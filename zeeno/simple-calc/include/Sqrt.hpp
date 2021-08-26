#pragma once
#ifndef _ZEENO_SQRT_HPP_
#	define _ZEENO_SQRT_HPP_

#	include "MathOperation.hpp"

class Sqrt final : public MathOperation {
public:
	size_t      maxOperands() const override;
	double      compute(const std::vector<double>& operands) const override;
	std::string preferredSymbol() const override;
};

#endif
