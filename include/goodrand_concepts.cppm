export module goodrand:concepts;

import std;

namespace launch {
	export template <typename T>
	concept distrib_int =
		std::is_same_v<short, T> ||
		std::is_same_v<int, T> ||
		std::is_same_v<long, T> ||
		std::is_same_v<long long, T> ||
		std::is_same_v<unsigned short, T> ||
		std::is_same_v<unsigned int, T> ||
		std::is_same_v<unsigned long, T> ||
		std::is_same_v<unsigned long long, T>;

	export template <typename T>
	concept distrib_real =
		std::is_same_v<float, T> ||
		std::is_same_v<double, T> ||
		std::is_same_v<long double, T>;
}