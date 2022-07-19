#pragma once
#ifndef CHIP_CLIENT_HPP
#	define CHIP_CLIENT_HPP

#	include <string.h>
#	include <chrono>
#	include <thread>
#	include <MQTTAsync.h>

#	include "configReader.hpp"

namespace mqtt {

class Client {
public:
	Client(ConfigurationSetting configurationData);

	virtual ~Client();

	void setOnMessageArrivedCallback(std::function<void(std::string, std::string)> callbackFunction);
	int  execution();
	void finish();

private:
	static void connlost(void* context, char* cause);
	static void onDisconnectFailure(void* context, MQTTAsync_failureData* response);
	static void onDisconnect(void* context, MQTTAsync_successData* response);
	static void onSendFailure(void* context, MQTTAsync_failureData* response);
	static void onSend(void* context, MQTTAsync_successData* response);
	static void onConnectFailure(void* context, MQTTAsync_failureData* response);
	static void onConnect(void* context, MQTTAsync_successData* response);
	static int  messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* m);

	ConfigurationSetting _cofinguration;
	std::jthread         _worker;

	MQTTAsync                   _client;
	int                         _returnCode{0};
	MQTTAsync_connectOptions    _connectOptions    = MQTTAsync_connectOptions_initializer;
	MQTTAsync_responseOptions   _responseOptions   = MQTTAsync_responseOptions_initializer;
	MQTTAsync_message           _message           = MQTTAsync_message_initializer;
	MQTTAsync_disconnectOptions _disconnectOptions = MQTTAsync_disconnectOptions_initializer;

	std::function<void(std::string, std::string)> _onMessageArrivedCallback;
};

} // namespace mqtt

#endif