#pragma once
#ifndef CHIP_CONFIG_READER_HPP
#	define CHIP_CONFIG_READER_HPP

#	include <cstdlib>
#	include <iostream>

#	include "nlohmann/json.hpp" //https://github.com/nlohmann/json

struct mqttServerConfiguration {
	std::string name;
	std::string ipAdress;
	uint16_t    port{80};
	std::string user;
	std::string password;
};

mqttServerConfiguration fromJson(const nlohmann::json&);

nlohmann::json loadJson(const std::string&);

std::ostream& operator<<(std::ostream&, const mqttServerConfiguration&);

#endif