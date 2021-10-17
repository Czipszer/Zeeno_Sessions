#include <string>

#include "MQTTAsync.h"

#include "configReader.hpp"
#include "counter.hpp"
#include "gauge.hpp"
#include "histogram.hpp"
#include "main.hpp"
#include "summary.hpp"

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

		std::unordered_map<std::string, std::string> emptyLabels;
		Histogram                                    hisbob("histogram", emptyLabels, {10.551, 30.1, 60, 90.14268742});
		std::cout << hisbob.getInfo() << std::endl;
		hisbob.addSample(10);
		hisbob.addSample(10.6);
		hisbob.addSample(500);
		std::cout << hisbob.getInfo() << std::endl;

		Summary sumbob("summaru", emptyLabels, {0.2, 0.5, 0.9}, std::chrono::minutes(5));
		std::cout << sumbob.getInfo() << std::endl;
		sumbob.addSample(30);
		sumbob.addSample(40);
		sumbob.addSample(20);
		sumbob.addSample(15);
		sumbob.addSample(30);
		sumbob.addSample(10);
		std::cout << sumbob.getInfo() << std::endl;

		return EXIT_SUCCESS;
	} catch (const std::exception& e) {
		std::cerr << e.what();
		return EXIT_FAILURE;
	}
}
