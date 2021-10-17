#pragma once
#ifndef CHIP_CONFIG_READER_HPP
#	define CHIP_CONFIG_READER_HPP

#	include <cstdlib>
#	include <iostream>

#	include "nlohmann/json.hpp" //https://github.com/nlohmann/json

struct MqttServerConfiguration {
	std::string name;
	std::string ipAdress;
	uint16_t    port{80};
	std::string user;
	std::string password;

	static MqttServerConfiguration fromJson(const nlohmann::json&);
};

nlohmann::json loadJson(const std::string&);

std::ostream& operator<<(std::ostream&, const MqttServerConfiguration&);

#endif