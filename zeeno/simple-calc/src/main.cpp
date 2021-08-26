#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "Addition.hpp"
#include "Echo.hpp"
#include "Pow.hpp"
#include "Sqrt.hpp"
#include "Subtraction.hpp"
#include "main.hpp"

const std::vector<std::shared_ptr<MathOperation>>
    operations{std::make_shared<Addition>(), std::make_shared<Subtraction>(), std::make_shared<Sqrt>(), std::make_shared<Pow>(), std::make_shared<Echo>()};

int main() {
	try {
		std::cout << "Enter a operation [";
		std::string symbols = std::accumulate(
		    operations.begin() + 1,
		    operations.end(),
		    (*operations.begin())->preferredSymbol(),
		    [](const std::string& symbols, const std::shared_ptr<MathOperation>& op) { return symbols + ", " + op->preferredSymbol(); });
		std::cout << symbols << "] (default = echo):";

		std::string operation;
		std::getline(std::cin, operation);

		auto op = std::ranges::find_if(operations, [operation](const std::shared_ptr<MathOperation>& op) { return op->canProcess(operation); });
		if (op == operations.end()) {
			std::cerr << "No processor can process your request." << std::endl;
			return EXIT_FAILURE;
		}

		std::cout << "Enter " << (*op)->minOperands() << "-" << (*op)->maxOperands() << " operands separated by a white space. At the end, make a new line."
		          << std::endl
		          << ":";

		auto arguments = parseLineAsTokens<double>(std::cin);
		if (arguments.size() < (*op)->minOperands() || arguments.size() > (*op)->maxOperands()) {
			std::cerr << "bad number of operands" << std::endl;
			return EXIT_FAILURE;
		}

		std::cout << "Result is: " << (*op)->compute(arguments) << std::endl;
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}