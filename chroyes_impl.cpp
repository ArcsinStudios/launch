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
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		start_time = now;
		stop_time = now;
		timing = false;
	}
	
	void stopwatch::start() {
		if (timing) {
			return;
		}
		timing = true;
		std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
		start_time = now;
		stop_time = now;
	}

	void stopwatch::stop() {
		if (!timing) {
			return;
		}
		timing = false;
		stop_time = std::chrono::high_resolution_clock::now();
	}

	duration stopwatch::get_duration() const {
		return duration(stop_time - start_time);
	}
}