# MQTT exporter

## Purpose
The purpose of this software will be to connect to MQTT broker, subscribe to the defined topics and publish it as Prometheus metrics file. Basically: start -> read configuration -> connect to the broker -> subscribe to the topics -> wait on message -> write to the file

## MQTT client
Mqtt client implementations (choose one)
- paho-mqtt-c - Chip
- paho-mqtt-cpp - bolci, Mliko
- mosquitto - Rainy

## Configuration file format
Configuration technologies (choose one)
- YAML - Rainy, Mliko
- JSON - Chip
- TOML - bolci

## Making a project

1. Search for the libraries on https://conan.io/center/ and write it to your conanfile.txt, then run file `conan_install.<bat|sh>` (2021-09-15)
1. Learn about your configuration file format and implement simple file loading (2021-09-19)
1. Learn about Prometheus and it's data types, implement type Counter (2021-09-26)
  - https://prometheus.io/docs/concepts/metric_types/ 
  - https://prometheus.io/docs/instrumenting/exposition_formats/
  - https://github.com/OpenObservability/OpenMetrics/blob/main/specification/OpenMetrics.md
1. Implement an output module that is able to manage many Prometheus types and output them into a file (path is configurable). Implement the rest of Prometheus types. (2021-10-3)
1. Make output period of the file configurable. (2021-10-17)
1. Learn about your MQTT client implementation and connect to the server. Subscribe and publish values. (2021-10-24)
1. Read from configuration file a list of topics to subscribe to. Parse the message and topic by a regex and print it on the screen. (2021-11-01)
1. Finish the project (2021-11-08)

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
