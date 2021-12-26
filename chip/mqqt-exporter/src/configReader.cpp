#include <fstream>
#include <string>

#include "configReader.hpp"
#include "myEXception.hpp"

using namespace nlohmann;

void from_json(const json& jsonFile, std::pair<std::string, std::string>& structure) {
	jsonFile.at("name").get_to(structure.first);
	jsonFile.at("value").get_to(structure.second);
}

void from_json(const json& jsonFile, MetricsData& structure) {
	jsonFile.at("topic").get_to(structure.topic);
	jsonFile.at("name").get_to(structure.name);
	jsonFile.at("labels").get_to(structure.labels);
	jsonFile.at("type").get_to(structure.type);
	jsonFile.at("unit").get_to(structure.unit);
	jsonFile.at("help").get_to(structure.help);
	jsonFile.at("timestemp").get_to(structure.timestemp);
}

ConfigurationSetting ConfigurationSetting::fromJson(const json& jsonFile) {
	ConfigurationSetting data;
	int                  timeout;
	int                  period;

	jsonFile.at("ipAdress").get_to(data.ipAdress);
	jsonFile.at("port").get_to(data.port);
	jsonFile.at("clientId").get_to(data.clientId);

	data.topics.push_back("FVE_Telc/+/Total");
	data.topics.push_back("FVE_Telc/+/Uac1");

	jsonFile.at("qos").get_to(data.qos);
	jsonFile.at("timeout").get_to(timeout);
	jsonFile.at("period").get_to(period);

	data.timeout = std::chrono::seconds(timeout);
	data.period  = std::chrono::milliseconds(period);

	std::ifstream myinput("configPokus.json");
	auto          j = json::parse(myinput);
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~ Pokus" << std::endl;
	std::cout << j << std::endl;
	//std::vector<std::pair<std::string, std::string>> v = j["labels"].get<std::pair<std::string, std::string>();
	std::pair<std::string, std::string> v = j.get<std::pair<std::string, std::string>>();
	//std::cout << v.first << " " << v.second << std::endl;
	//data.dataSets.labels                               = v;

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