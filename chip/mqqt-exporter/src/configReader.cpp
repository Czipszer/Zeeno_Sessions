#include <fstream>
#include <string>

#include "configReader.hpp"
#include "myEXception.hpp"

using namespace nlohmann;

void from_json(const json& jsonFile, MetricsData& structure) {
	jsonFile.at("topic").get_to(structure.topic);
	jsonFile.at("name").get_to(structure.name);

	for (auto label : jsonFile["labels"]) {
		structure.labels.emplace_back(label["name"].get<std::string>(), label["value"].get<std::string>());
	}

	jsonFile.at("type").get_to(structure.type);
	jsonFile.at("unit").get_to(structure.unit);
	jsonFile.at("help").get_to(structure.help);

	for (auto bucketOrQuantile : jsonFile["bucketsOrQuantiles"]) {
		structure.bucketsOrQuantiles.emplace_back(bucketOrQuantile.get<double>());
	}

	jsonFile.at("timestemp").get_to(structure.timestemp);
}

ConfigurationSetting ConfigurationSetting::fromJson(const json& jsonFile) {
	ConfigurationSetting data;
	int                  timeout;
	int                  periodWait;
	int                  periodWrite;

	jsonFile.at("ipAdress").get_to(data.ipAdress);
	jsonFile.at("port").get_to(data.port);
	jsonFile.at("clientId").get_to(data.clientId);
	jsonFile.at("qos").get_to(data.qos);
	jsonFile.at("timeout").get_to(timeout);
	jsonFile.at("periodWait").get_to(periodWait);
	jsonFile.at("periodWrite").get_to(periodWrite);

	data.timeout     = std::chrono::seconds(timeout);
	data.periodWait  = std::chrono::milliseconds(periodWait);
	data.periodWrite = std::chrono::seconds(periodWrite);

	std::vector<MetricsData> dataSets = jsonFile["dataSets"];
	data.dataSets                     = dataSets;

	for (auto topic : data.dataSets) {
		data.topics.push_back(topic.topic);
	}

	return data;
}

json loadJson(const std::string& pathToFile) {
	std::ifstream myJsonFile(pathToFile);

	json myJson;
	if (myJsonFile.is_open()) {
		myJson = json::parse(myJsonFile);
		myJsonFile.close();
	} else {
		throw FileExcept("Unable to open file", -10);
	}

	return myJson;
}

std::ostream& operator<<(std::ostream& os, const ConfigurationSetting& data) {
	return os << "Mqtt server:" << std::endl << "\ttarget: \t" << data.ipAdress << ":" << data.port << std::endl;
}