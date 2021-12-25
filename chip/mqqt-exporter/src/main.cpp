#include <MQTTAsync.h>
#include <string>

#include "configReader.hpp"
#include "counter.hpp"
#include "gauge.hpp"
#include "histogram.hpp"
#include "metricWriter.hpp"
#include "mqtt/client.hpp"
#include "myEXception.hpp"
#include "summary.hpp"

using namespace nlohmann;

int main() {
	try {
		// nacteni konfigurace
		json                 configFile = loadJson("config.json");
		ConfigurationSetting data{ConfigurationSetting::fromJson(configFile)};
		std::cout << data << std::endl;

		// vytvoreni labels
		std::unordered_map<std::string, std::string> labels = {{"Teplota", "pokoje"}, {"Humanity", "pokoje"}};
		// test counter
		auto counterTest = std::make_shared<Counter>("counter", labels, 854);
		// edit
		counterTest->setUnit("kelvin");
		counterTest->incValue();

		// test histogram
		auto histogramTest = std::make_shared<Histogram>("histogram", labels, std::vector<double>{10.551, 30.1, 60.0, 90.14268742});
		// edit
		histogramTest->setUnit("celsium");
		histogramTest->addSample(10);
		histogramTest->addSample(10.6);
		histogramTest->addSample(500);

		// test summary
		auto summaryTest = std::make_shared<Summary>("summaru", labels, std::vector<double>{0.2, 0.5, 0.9}, std::chrono::minutes(5));
		// edit
		summaryTest->setUnit("faradai");
		summaryTest->addSample(30);
		summaryTest->addSample(40);
		summaryTest->addSample(20);
		summaryTest->addSample(15);
		summaryTest->addSample(30);
		summaryTest->addSample(10);

		//test odesilani dat na MQTT brokera
		mqtt::Client mqttClient(data);

		mqttClient.execution();

		// test vypisu do souboru
		//vytvoreni ukazatelu na vector
		auto metrics = std::make_shared<std::vector<std::shared_ptr<Metric>>>();
		// naplneni tohoto vektoru
		metrics->push_back(counterTest);
		metrics->push_back(histogramTest);
		metrics->push_back(summaryTest);
		// deklarace class pro vypis
		MetricWriter writer("output.txt", metrics, std::chrono::seconds(2));
		// periodicky vypis
		writer.periodicWrite();

		// ukonceni smycek
		std::cout << "Press ENTER to end the program" << std::endl;
		std::cin.get();

		mqttClient.finish();
		writer.finish();

		return EXIT_SUCCESS;
	} catch (const FileExcept& e) {
		std::cerr << "Error number: " << e.getErrorNumber() << std::endl << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
