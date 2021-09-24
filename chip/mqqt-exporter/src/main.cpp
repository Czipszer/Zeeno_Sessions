#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "MQTTAsync.h"
#include "main.hpp"

using namespace std;

int main() {
	try {
		return EXIT_SUCCESS;
	} catch (const exception& e) {
		cerr << e.what();
		return EXIT_FAILURE;
	}
}
