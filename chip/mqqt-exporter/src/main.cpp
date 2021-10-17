#include <string>

#include "MQTTAsync.h"
#include "configReader.hpp"
#include "counter.hpp"
#include "gauge.hpp"
#include "histogram.hpp"
#include "main.hpp"

using namespace nlohmann;

int main() {
	try {
		json                    file = loadJson("config.json");
		MqttServerConfiguration data{MqttServerConfiguration::fromJson(file)};
		std::cout << data << std::endl;

		std::unordered_map<std::string, std::string> labels = {{"ahoj", "vole"}, {"jako", "prak"}};
		Counter                                      cntr("Counter", labels, 854);
		std::cout << cntr.getInfo() << std::endl;
		cntr.incValue();
		std::cout << cntr.getInfo() << std::endl;

		Histogram hisbob1("histogram", labels, {10, 30, 60, 90});
		std::cout << hisbob1.getInfo() << std::endl;

		std::unordered_map<std::string, std::string> emptyLabels;
		Histogram                                    hisbob2("histogram", emptyLabels, {10.551, 30.1, 60, 90.14268742});
		std::cout << hisbob2.getInfo() << std::endl;

		return EXIT_SUCCESS;
	} catch (const std::exception& e) {
		std::cerr << e.what();
		return EXIT_FAILURE;
	}
}
