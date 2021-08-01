#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <unordered_map>

#include "main.hpp"

using CalculatorType = double;

const std::unordered_map<std::string, std::function<CalculatorType(const CalculatorType&, const CalculatorType&)>> operations{
    {"+", std::plus<CalculatorType>{}},
    {"-", std::minus<CalculatorType>{}},
    {"*", std::multiplies<CalculatorType>{}},
    {"/", std::divides<CalculatorType>{}},
    {"pow", [](const CalculatorType& a, const CalculatorType& b) {
	     if (b == 0) {
		     throw std::runtime_error("Not here!");
	     }
	     return std::pow(a, b);
     }}};

int main() {
	try {
		auto a  = readFromCin<CalculatorType>("First number: ");
		auto op = readFromCin<std::string>("Op (+, -, *, /, pow) is: ");
		auto b  = readFromCin<CalculatorType>("Second number: ");

		if (!operations.contains(op)) {
			throw std::runtime_error("Unknown operation");
		}

		auto operation = operations.at(op);

		std::cout << "Result is: " << operation(a, b) << std::endl;

	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}