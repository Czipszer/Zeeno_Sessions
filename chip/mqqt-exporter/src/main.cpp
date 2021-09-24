#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "main.hpp"

using namespace std;

int main() {
	try {
		return 0;
	} catch (const exception& e) {
		cerr << e.what();
		return 1;
	}
}
