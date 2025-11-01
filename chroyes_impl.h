#pragma once

#include <chrono>

namespace launch {
	class duration {
	private:
		std::chrono::nanoseconds ns;

	public:
		duration() = default;

		explicit duration(std::chrono::nanoseconds _ns) : ns(_ns) {}

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
		bool timing;

	public:
		stopwatch();

		void start();

		void stop();

		duration get_duration() const;
	};
}