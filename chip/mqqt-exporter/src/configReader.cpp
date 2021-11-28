#include <fstream>
#include <string>

#include "configReader.hpp"
#include "myEXception.hpp"

using namespace nlohmann;

MqttServerConfiguration MqttServerConfiguration::fromJson(const json& jsonFile) {
	MqttServerConfiguration data;

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
		throw FileExcept("Unable to open file", -10);
	}

	return myJson;
};

std::ostream& operator<<(std::ostream& os, const MqttServerConfiguration& data) {
	return os << "Mqtt server:" << std::endl
	          << "\tname: \t\t" << data.name << std::endl
	          << "\ttarget: \t" << data.ipAdress << ":" << data.port << std::endl
	          << "\tusername: \t" << data.user << std::endl
	          << "\tpassword: \t" << data.password << std::endl;
};