#pragma once
#ifndef CHIP_CONFIG_READER_HPP
#	define CHIP_CONFIG_READER_HPP

#	include <cstdlib>
#	include <iostream>
#	include <vector>
#	include <chrono>

#	include "nlohmann/json.hpp" //https://github.com/nlohmann/json

struct MetricsData {
	std::string                                      topic;
	std::string                                      name;
	std::vector<std::pair<std::string, std::string>> labels;
	std::string                                      type;
	std::string                                      unit;
	std::string                                      help;
	int                                              timestemp{0};
};

class ConfigurationSetting {
public:
	static ConfigurationSetting fromJson(const nlohmann::json&);

	std::string              ipAdress{"tcp://eu1.broker.rechip.eu"};
	std::string              port{"80"};
	std::string              clientId;
	std::vector<std::string> topics;
	//std::vector<MetricsData>  dataSets;
	MetricsData               dataSets;
	int                       qos{0};
	std::chrono::seconds      timeout;
	std::chrono::milliseconds period;
};

nlohmann::json loadJson(const std::string&);

std::ostream& operator<<(std::ostream&, const ConfigurationSetting&);

#endif