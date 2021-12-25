#pragma once
#ifndef CHIP_CONFIG_READER_HPP
#	define CHIP_CONFIG_READER_HPP

#	include <cstdlib>
#	include <iostream>
#	include <vector>
#	include <chrono>

#	include "nlohmann/json.hpp" //https://github.com/nlohmann/json

struct ConfigurationSetting {
	std::string               ipAdress{"tcp://eu1.broker.rechip.eu"};
	std::string               port{"80"};
	std::string               clientId;
	std::vector<std::string>  topics;
	int                       qos{0};
	std::chrono::seconds      timeout;
	std::chrono::milliseconds period;

	static ConfigurationSetting fromJson(const nlohmann::json&);
};

nlohmann::json loadJson(const std::string&);

std::ostream& operator<<(std::ostream&, const ConfigurationSetting&);

#endif