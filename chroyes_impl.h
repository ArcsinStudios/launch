#pragma once

#include <chrono>

namespace launch {
	class duration {
	private:
		std::chrono::nanoseconds ns;

	public:
		duration() = default;

		duration(std::chrono::nanoseconds _ns) : ns(_ns) {}

		duration& operator=(std::chrono::nanoseconds _ns);

		long long seconds() const;

		long long milliseconds() const;

		long long microseconds() const ;

		long long nanoseconds() const ;

		std::chrono::nanoseconds std_nanoseconds() const ;
	};

	class stopwatch {
	private:
		std::chrono::high_resolution_clock::time_point start_time;
		std::chrono::high_resolution_clock::time_point stop_time;
		std::chrono::high_resolution_clock::time_point pause_start;
		std::chrono::high_resolution_clock::time_point pause_stop;
		duration pause_dur;

	public:
		stopwatch();

		void start();

		void stop();

		void pause();

		void resume();

		duration get_duration() const;
	};
}