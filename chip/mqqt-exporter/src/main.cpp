#include <MQTTAsync.h>
#include <string>

#include "businessLogic.hpp"
#include "configReader.hpp"
#include "counter.hpp"
#include "gauge.hpp"
#include "histogram.hpp"
#include "metric.hpp"
#include "metricWriter.hpp"
#include "mqtt/client.hpp"
#include "myException.hpp"
#include "summary.hpp"


using namespace nlohmann;

int main() {
	try {
		// nacteni konfigurace
		json                 configFile = loadJson("config.json");
		ConfigurationSetting data{ConfigurationSetting::fromJson(configFile)};
		std::cout << data << std::endl;

		// vytvoreni sdilenych metric
		BusinessLogic metrics(data.dataSets);

		// hlaska pro ukonceni
		std::cout << "~~~~~~~~ Press ENTER to end the program ~~~~~~~~" << std::endl << std::endl;

		// test odesilani dat na MQTT brokera
		mqtt::Client mqttClient(data);
		mqttClient.setOnMessageArrivedCallback([&metrics](const std::string& topic, const std::string& value) { metrics.processMessage(topic, value); });

		mqttClient.execution();

		// deklarace class pro vypis
		MetricWriter writer("output.txt", metrics.getMetrics(), data.periodWrite);
		// periodicky vypis
		writer.periodicWrite();

		// ukonceni smycek
		std::cin.get();
		mqttClient.finish();
		writer.finish();

		return EXIT_SUCCESS;
	} catch (const FileExcept& e) {
		std::cerr << "Error number: " << e.getErrorNumber() << std::endl << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
