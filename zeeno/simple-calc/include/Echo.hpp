#pragma once
#ifndef _ZEENO_ECHO_HPP_
#	define _ZEENO_ECHO_HPP_

#	include "MathOperation.hpp"

class Echo final : public MathOperation {
public:
	size_t      maxOperands() const override;
	bool        canProcess(const std::string&) const override;
	double      compute(const std::vector<double>& operands) const override;
	std::string preferredSymbol() const override;
};

#endif
