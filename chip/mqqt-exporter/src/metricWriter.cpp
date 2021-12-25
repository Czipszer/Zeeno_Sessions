#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "metricWriter.hpp"
#include "myEXception.hpp"

using namespace std;

MetricWriter::MetricWriter(string newNameFile, shared_ptr<vector<shared_ptr<Metric>>> newMetrics, chrono::seconds newWritePeriod)
    : _nameFile{newNameFile}, _metrics{newMetrics}, _writePeriod{newWritePeriod} {
}

MetricWriter::~MetricWriter() {
}

void MetricWriter::periodicWrite() {
	fstream file;

	file.open(_nameFile, fstream::binary | fstream::trunc | fstream::out);

	if (!file.is_open()) {
		throw FileExcept("Unable to open file", -10);
	}

	for (auto metric : *_metrics) {
		file << metric->getHead() << metric->getInfo() << endl << endl;
	}

	_worker = jthread([this](std::stop_token token) {
		while (!token.stop_requested()) {
			//std::cout << "Metrics was writed to output file" << std::endl;

			this_thread::sleep_for(_writePeriod);
		}
	});
	file.close();
}

void MetricWriter::finish() {
	_worker.request_stop();

	if (_worker.joinable()) {
		_worker.join();
	}
}