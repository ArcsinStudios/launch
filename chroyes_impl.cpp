#include "chroyes_impl.h"

namespace launch {
	duration& duration::operator=(std::chrono::nanoseconds _ns) {
		ns = _ns;
		return *this;
	}

	long long duration::seconds() const {
		return std::chrono::duration_cast<std::chrono::seconds>(ns).count();
	}

	long long duration::milliseconds() const {
		return std::chrono::duration_cast<std::chrono::milliseconds>(ns).count();
	}


	long long duration::microseconds() const {
		return std::chrono::duration_cast<std::chrono::microseconds>(ns).count();
	}

	long long duration::nanoseconds() const {
		return ns.count();
	}

	std::chrono::nanoseconds duration::std_nanoseconds() const {
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

	duration stopwatch::get_duration() const {
		return dur;
	}
}