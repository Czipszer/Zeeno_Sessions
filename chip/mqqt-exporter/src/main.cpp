#include <string>

#include "MQTTAsync.h"
#include "configReader.hpp"
#include "counter.hpp"
#include "main.hpp"

using namespace nlohmann;

int main() {
	try {
		json                    file = loadJson("config.json");
		mqttServerConfiguration data = fromJson(file);
		std::cout << data << std::endl;

		std::unordered_map<std::string, std::string> labels = {{"ahoj", "vole"}, {"jako", "prak"}};
		Counter                                      cntr("Counter", labels, 854);
		std::cout << cntr.getInfo() << std::endl;
		cntr.incValue();
		std::cout << cntr.getInfo() << std::endl;

		return EXIT_SUCCESS;
	} catch (const std::exception& e) {
		std::cerr << e.what();
		return EXIT_FAILURE;
	}
}
