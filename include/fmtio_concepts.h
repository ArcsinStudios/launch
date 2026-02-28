#pragma once

#include <concepts>
#include <iostream>

namespace launch {
	template <typename T>
	concept readable = requires(std::istream& in, T& x) {
		{ in >> x } -> std::same_as<std::istream&>;
	};
}