#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include "mqtt/client.hpp"
#include "myEXception.hpp"

using namespace std;

int mqttFinished{0};
int mqttDisconnectFinished{0};
int mqttSubscribed{0};
int mqttConnected{0};

mqtt::Client::Client(ConfigurationSetting newConfigurationData) : _cofinguration{newConfigurationData} {
}

mqtt::Client::~Client() {
}

void mqtt::Client::finish() {
	mqttFinished  = 1;
	mqttConnected = 1;
}

void mqtt::Client::connlost(void* context, char* cause) {
	MQTTAsync                client         = (MQTTAsync) context;
	MQTTAsync_connectOptions connectOptions = MQTTAsync_connectOptions_initializer;
	int                      returnCode;

	cout << endl << "Connection lost cause: " << cause << endl;

	cout << "Reconnecting" << endl;

	connectOptions.keepAliveInterval = 20;
	connectOptions.cleansession      = 1;

	if ((returnCode = MQTTAsync_connect(client, &connectOptions)) != MQTTASYNC_SUCCESS) {
		cout << "Failed to start connect, return code" << returnCode;

		mqttFinished = 1;
	}
}

void mqtt::Client::onDisconnectFailure(void* /*context*/, MQTTAsync_failureData* /*response*/) {
	cout << "Disconnect failed" << endl;

	mqttDisconnectFinished = 1;
}

void mqtt::Client::onDisconnect(void* /*context*/, MQTTAsync_successData* /*response*/) {
	cout << "Successful disconnection" << endl;

	mqttDisconnectFinished = 1;
}

void mqtt::Client::onSendFailure(void* /*context*/, MQTTAsync_failureData* response) {
	cout << "Message send failed token " << response->token << "error code " << response->code << endl << endl;

	mqttFinished = 1;
}

void mqtt::Client::onSend(void* /*context*/, MQTTAsync_successData* response) {
	cout << "Message with token value " << response->token << " delivery confirmed" << endl << endl;
}

void mqtt::Client::onConnectFailure(void* /*context*/, MQTTAsync_failureData* response) {
	cout << "Connect failed, returnCode " << response->code << endl;

	mqttFinished = 1;
}

void mqtt::Client::onConnect(void* /*context*/, MQTTAsync_successData* /*response*/) {
	//Client* This = static_cast<Client*>(context);
	cout << "Successful connection" << endl;

	mqttConnected = 1;
}

void onSubscribeFailure(void* /*context*/, MQTTAsync_failureData* response) {
	cout << "Subscribe failed, returnCode " << response->code << endl;

	mqttFinished = 1;
}

void onSubscribe(void* /*context*/, MQTTAsync_successData* /*response*/) {
	cout << "Subscribe succeeded" << endl;

	mqttSubscribed = 1;
}

int mqtt::Client::messageArrived(void* /*context*/, char* topicName, int /*topicLen*/, MQTTAsync_message* message) {
	cout << "Message arrived" << endl;
	cout << "topic: " << topicName << endl;
	cout << "message: " << static_cast<char*>(message->payload) << endl << endl;

	MQTTAsync_freeMessage(&message);
	MQTTAsync_free(topicName);

	return 1;
}

int mqtt::Client::execution() {
	string address = _cofinguration.ipAdress + ":" + _cofinguration.port;

	if ((_returnCode = MQTTAsync_create(&_client, address.c_str(), _cofinguration.clientId.c_str(), MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTASYNC_SUCCESS) {
		cout << "Failed to create client object, return code " << _returnCode << endl;
		_returnCode = EXIT_FAILURE;
		return _returnCode;
	}

	if ((_returnCode = MQTTAsync_setCallbacks(_client, _client, connlost, messageArrived, NULL)) != MQTTASYNC_SUCCESS) {
		cout << "Failed to set callback, return code " << _returnCode << endl;
		_returnCode = EXIT_FAILURE;
		MQTTAsync_destroy(&_client);
		return _returnCode;
	}

	_connectOptions.keepAliveInterval = 20;
	_connectOptions.cleansession      = 1;
	_connectOptions.onSuccess         = onConnect;
	_connectOptions.onFailure         = onConnectFailure;
	_connectOptions.context           = _client;

	if ((_returnCode = MQTTAsync_connect(_client, &_connectOptions)) != MQTTASYNC_SUCCESS) {
		cout << "Failed to start connect, return code " << _returnCode << endl;
		_returnCode = EXIT_FAILURE;
		MQTTAsync_destroy(&_client);
		return _returnCode;
	}

	_worker = jthread([this]() {
		int iteration{1};

		while (!mqttConnected && !mqttSubscribed) {
			cout << "Waiting on connection to MQTT broker, attempt " << iteration << endl;

			this_thread::sleep_for(_cofinguration.timeout);

			iteration++;

			if (iteration >= 4) {
				mqttConnected  = 1;
				mqttSubscribed = 1;
				mqttFinished   = 1;
			}
		}

		for (auto vectorIteration : _cofinguration.topics) {
			cout << "Subscribing to topic " << vectorIteration << endl
			     << "for client " << _cofinguration.clientId << " using QoS: " << _cofinguration.qos << endl;

			_responseOptions.onSuccess = onSubscribe;
			_responseOptions.onFailure = onSubscribeFailure;
			_responseOptions.context   = _client;

			if ((_returnCode = MQTTAsync_subscribe(_client, vectorIteration.c_str(), _cofinguration.qos, &_responseOptions)) != MQTTASYNC_SUCCESS) {
				printf("Failed to start subscribe, return code %d\n", _returnCode);
				mqttFinished = 1;
			}

			this_thread::sleep_for(chrono::milliseconds(100));
		}

		while (!mqttFinished) {
			this_thread::sleep_for(_cofinguration.period);
		}

		if (mqttFinished) {
			_disconnectOptions.onSuccess = onDisconnect;
			_disconnectOptions.onFailure = onDisconnectFailure;

			if ((_returnCode = MQTTAsync_disconnect(_client, &_disconnectOptions)) != MQTTASYNC_SUCCESS) {
				cout << "Failed to start disconnect, return code " << _returnCode << endl;
				_returnCode = EXIT_FAILURE;
				MQTTAsync_destroy(&_client);
				return _returnCode;
			}

			iteration = 1;

			while (!mqttDisconnectFinished) {
				cout << "Waiting on disconnection from MQTT broker, attempt " << iteration << endl;

				this_thread::sleep_for(_cofinguration.timeout);

				iteration++;

				if (iteration >= 4) {
					mqttDisconnectFinished = 1;
				}
			}

			MQTTAsync_destroy(&_client);

			mqttFinished           = 0;
			mqttDisconnectFinished = 0;
			mqttSubscribed         = 0;
			mqttConnected          = 0;

			return _returnCode;
		}
	});
}