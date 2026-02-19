#pragma once

#include <limits>
#include <random>

#include "goodrand_concepts.h"

namespace launch {

	template <distrib_int T>
	class randgen_int {
	private:
		std::random_device rd;
		std::mt19937_64 engine;
		std::uniform_int_distribution<T> distrib;

	public:
		randgen_int(
			T min = std::numeric_limits<T>::min(),
			T max = std::numeric_limits<T>::max()
		) : engine(rd()), distrib(min, max) {}

		void set_range(T min, T max) {
			distrib.param(std::uniform_int_distribution<T>::param_type(min, max));
		}

		T next() {
			return distrib(engine);
		}

		void reset() {
			distrib.reset();
		}

		void seed(std::random_device::result_type seed) {
			engine.seed(seed);
		}
	};

	template <distrib_real T>
	class randgen_real {
	private:
		std::random_device rd;
		std::mt19937_64 engine;
		std::uniform_real_distribution<T> distrib;

	public:
		randgen_real(
			T min = 0,
			T max = 1
		) : engine(rd()), distrib(min, max) {}

		void set_range(T min, T max) {
			distrib.param(std::uniform_real_distribution<T>::param_type(min, max));
		}

		T next() {
			return distrib(engine);
		}

		void reset() {
			distrib.reset();
		}

		void seed(std::random_device::result_type seed) {
			engine.seed(seed);
		}
	};
}