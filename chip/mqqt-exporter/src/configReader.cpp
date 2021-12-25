#include <fstream>
#include <string>

#include "configReader.hpp"
#include "myEXception.hpp"

using namespace nlohmann;

ConfigurationSetting ConfigurationSetting::fromJson(const json& jsonFile) {
	ConfigurationSetting data;
	int                  timeout;
	int                  period;

	jsonFile.at("ipAdress").get_to(data.ipAdress);
	jsonFile.at("port").get_to(data.port);
	jsonFile.at("clientId").get_to(data.clientId);

	//jsonFile.at("topic").get_to(data.topics);

	data.topics.push_back("FVE_Telc/+/Total");
	data.topics.push_back("FVE_Telc/+/Uac1");

	jsonFile.at("qos").get_to(data.qos);
	jsonFile.at("timeout").get_to(timeout);
	jsonFile.at("period").get_to(period);

	data.timeout = std::chrono::seconds(timeout);
	data.period  = std::chrono::milliseconds(period);

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
};

std::ostream& operator<<(std::ostream& os, const ConfigurationSetting& data) {
	return os << "Mqtt server:" << std::endl << "\ttarget: \t" << data.ipAdress << ":" << data.port << std::endl;
};