#pragma once

#include <chrono>

namespace launch {
	class timespan {
	private:
		std::chrono::nanoseconds ns;

	public:
		timespan() = default;

		explicit timespan(std::chrono::nanoseconds _ns) : ns(_ns) {}

		timespan& operator=(std::chrono::nanoseconds _ns);

		long long seconds() const;

		long long milliseconds() const;

		long long microseconds() const ;

		long long nanoseconds() const ;

		std::chrono::nanoseconds std_nanoseconds() const ;
	};

	class stopwatch {
	private:
		std::chrono::high_resolution_clock::time_point start_time;
		timespan dur;
		bool timing;
		bool pausing;

	public:
		stopwatch();

		void start();

		void stop();

		void pause();

		void resume();

		timespan get_dur() const;
	};
}