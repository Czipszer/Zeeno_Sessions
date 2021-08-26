#pragma once
#ifndef _ZEENO_ADDITION_HPP_
#	define _ZEENO_ADDITION_HPP_

#	include "MathOperation.hpp"

class Addition final : public MathOperation {
public:
	bool        canProcess(const std::string& symbol) const override;
	double      compute(const std::vector<double>& operands) const override;
	std::string preferredSymbol() const override;
};

#endif
