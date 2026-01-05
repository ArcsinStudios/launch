#include "launch_config.h"

#include "chroyes_impl.h"

namespace launch {
	timespan& timespan::operator=(std::chrono::nanoseconds _ns) {
		ns = _ns;
		return *this;
	}

	long long timespan::seconds() const {
		return std::chrono::duration_cast<std::chrono::seconds>(ns).count();
	}

	long long timespan::milliseconds() const {
		return std::chrono::duration_cast<std::chrono::milliseconds>(ns).count();
	}


	long long timespan::microseconds() const {
		return std::chrono::duration_cast<std::chrono::microseconds>(ns).count();
	}

	long long timespan::nanoseconds() const {
		return ns.count();
	}

	std::chrono::nanoseconds timespan::std_nanoseconds() const {
		return ns;
	}

	stopwatch::stopwatch() {
		start_time = std::chrono::high_resolution_clock::now();
		dur = std::chrono::nanoseconds(0);
		timing = false;
		pausing = false;
	}
	
	void stopwatch::start() {
		if (timing) {
			return;
		}
		start_time = std::chrono::high_resolution_clock::now();
		dur = std::chrono::nanoseconds(0);
		timing = true;
	}

	void stopwatch::stop() {
		if (!timing) {
			return;
		}
		dur = dur.std_nanoseconds() + (std::chrono::high_resolution_clock::now() - start_time);
		timing = false;
	}

	void stopwatch::pause() {
		if (pausing) {
			return;
		}
		dur = dur.std_nanoseconds() + (std::chrono::high_resolution_clock::now() - start_time);
		pausing = true;
	}

	void stopwatch::resume() {
		if (!pausing) {
			return;
		}
		start_time = std::chrono::high_resolution_clock::now();
		pausing = false;
	}

	timespan stopwatch::get_dur() const {
		return dur;
	}
}