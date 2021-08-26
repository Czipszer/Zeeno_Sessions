#pragma once
#ifndef _ZEENO_MATH_OPERATION_HPP_
#	define _ZEENO_MATH_OPERATION_HPP_

#	include <string>
#	include <vector>

class MathOperation {
public:
	virtual double      compute(const std::vector<double>& operands) const = 0;
	virtual std::string preferredSymbol() const                            = 0;
	virtual bool        canProcess(const std::string& symbol) const;
	virtual size_t      minOperands() const;
	virtual size_t      maxOperands() const;
};

#endif
