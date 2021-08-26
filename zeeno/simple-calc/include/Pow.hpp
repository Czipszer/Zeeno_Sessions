#pragma once
#ifndef _ZEENO_POW_HPP_
#	define _ZEENO_POW_HPP_

#	include "MathOperation.hpp"

class Pow final : public MathOperation {
public:
	size_t      maxOperands() const override;
	size_t      minOperands() const override;
	double      compute(const std::vector<double>& operands) const override;
	std::string preferredSymbol() const override;
};

#endif
