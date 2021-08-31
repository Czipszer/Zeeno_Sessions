#include <functional>
#include <iostream>
#include <map>
#include <string>

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
