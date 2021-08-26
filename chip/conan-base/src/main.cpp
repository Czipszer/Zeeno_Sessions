#include <cstdlib>
#include <iostream>
#include <mosquitto.h>

int main(int argc, char* argv[]) {
	mosquitto_lib_init();
	std::cout << "Hell"
	          << "o world" << std::endl;
	mosquitto_lib_cleanup();
	return EXIT_SUCCESS;
}