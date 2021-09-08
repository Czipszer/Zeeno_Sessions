# MQTT exporter

## Purpose
The purpose of this software will be to connect to MQTT broker, subscribe to the defined topics and publish it as Prometheus metrics file. Basically: start -> read configuration -> connect to the broker -> subscribe to the topics -> wait on message -> write to the file

## MQTT client
Mqtt client implementations (choose one)
- paho-mqtt-c - Chip
- paho-mqtt-cpp
- mosquitto

## Configuration file format
Configuration technologies (choose one)
- YAML
- JSON - Chip
- TOML

## Starting a project

1. Search for the libraries on https://conan.io/center/ and write it to your conanfile.txt, then run file `conan_install.<bat|sh>`
1. Learn about MQTT, how it operates
1. Design an application architecture
    - components
	- classes
	- communication diagram
	- responsibilities
1. Get feedback

## Requirements
- Configurable MQTT server
- Secure connection to MQTT broker
- Reconnection on MQTT broker connection fail
- Configurable metrics
	- MQTT related stuff
		- Topic to listen to (including wildcards)
		- Regex to parse device-id from the topic
		- Regex (or json path) to parse data from the message
	- Prometheus related stuff
		- Type of the metric https://prometheus.io/docs/concepts/metric_types/
		- Metric-specific stuff (like values of the buckets)
		- Name
		- Help
		- Labels
- Configurable output file
- Configurable output file period (not to generate the file thousand times a second)
- Support for variables, so I can put a topic name or device-id into the label
- Ability to parse multiple values out of one message
