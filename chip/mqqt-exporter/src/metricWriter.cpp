#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

#include "metric.hpp"
#include "metricWriter.hpp"
#include "myEXception.hpp"

using namespace std;

MetricWriter::MetricWriter(string newNameFile, shared_ptr<Metrics> newMetrics, chrono::seconds newWritePeriod)
    : _nameFile{newNameFile}, _metrics{newMetrics}, _writePeriod{newWritePeriod} {
}

MetricWriter::~MetricWriter() {
}

void MetricWriter::periodicWrite() {
	//fstream file;

	_worker = jthread([this](std::stop_token token) {
		while (!token.stop_requested()) {
			_file.open(_nameFile, fstream::binary | fstream::trunc | fstream::out);

			if (!_file.is_open()) {
				throw FileExcept("Unable to open file", -10);
			}

			{
				scoped_lock lock{_metrics->mutex};

				sort(_metrics->metrics.begin(), _metrics->metrics.end(), [](shared_ptr<Metric> a, shared_ptr<Metric> b) { return a->getName() < b->getName(); });

				string memoryName;

				for (auto metric : _metrics->metrics) {
					if (memoryName != metric->getName()) {
						if (!memoryName.empty()) {
							_file << endl;
						}

						_file << metric->getHead();
					}

					_file << metric->getInfo() << endl;

					memoryName = metric->getName();
				}
			}

			_file.close();

			cout << endl << "Metrics was writed to output file" << endl << endl;

			this_thread::sleep_for(_writePeriod);
		}
	});
}

void MetricWriter::finish() {
	_worker.request_stop();

	if (_worker.joinable()) {
		_worker.join();
	}
}