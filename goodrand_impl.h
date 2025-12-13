#pragma once

#include <limits>
#include <random>

namespace launch {
	template <typename T>
	concept DistribIntType =
		std::is_same_v<short, T> ||
		std::is_same_v<int, T> ||
		std::is_same_v<long, T> ||
		std::is_same_v<long long, T> ||
		std::is_same_v<unsigned short, T> ||
		std::is_same_v<unsigned int, T> ||
		std::is_same_v<unsigned long, T> ||
		std::is_same_v<unsigned long long, T>;

	template <typename T>
	concept DistribRealType =
		std::is_same_v<float, T> ||
		std::is_same_v<double, T> ||
		std::is_same_v<long double, T>;

	template <DistribIntType T>
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

		randgen_int(
			std::random_device::result_type seed,
			T min = std::numeric_limits<T>::min(),
			T max = std::numeric_limits<T>::max()
		) : engine(seed), distrib(min, max) {}

		void set_range(T min, T max) {
			distrib.param(std::uniform_int_distribution<T>::param_type(min, max));
		}

		T next() {
			return distrib(engine);
		}

		void reset() {
			distrib.reset();
		}

		void resow(std::random_device::result_type seed) {
			engine.seed(seed);
		}
	};

	template <DistribRealType T>
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

		randgen_real(
			std::random_device::result_type seed,
			T min = 0,
			T max = 1
		) : engine(seed), distrib(min, max) {}

		void set_range(T min, T max) {
			distrib.param(std::uniform_real_distribution<T>::param_type(min, max));
		}

		T next() {
			return distrib(engine);
		}

		void reset() {
			distrib.reset();
		}

		void resow(std::random_device::result_type seed) {
			engine.seed(seed);
		}
	};
}