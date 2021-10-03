#include <fstream>
#include <string>

#include "configReader.hpp"

using namespace nlohmann;

mqttServerConfiguration fromJson(const json& jsonFile) {
	mqttServerConfiguration data;

	jsonFile.at("name").get_to(data.name);
	jsonFile.at("ipAdress").get_to(data.ipAdress);
	jsonFile.at("port").get_to(data.port);
	jsonFile.at("user").get_to(data.user);
	jsonFile.at("password").get_to(data.password);

	return data;
}

json loadJson(const std::string& pathToFile) {
	std::ifstream myJsonFile(pathToFile);

	json myJson;
	if (myJsonFile.is_open()) {
		myJson = json::parse(myJsonFile);
		myJsonFile.close();
	} else {
		throw std::runtime_error("Unable to open file");
	}

	return myJson;
};

std::ostream& operator<<(std::ostream& os, const mqttServerConfiguration& data) {
	return os << "Mqtt server:" << std::endl
	          << "\tname: \t\t" << data.name << std::endl
	          << "\ttarget: \t" << data.ipAdress << ":" << data.port << std::endl
	          << "\tusername: \t" << data.user << std::endl
	          << "\tpassword: \t" << data.password << std::endl;
};