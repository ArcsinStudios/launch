#pragma once

#include <concepts>
#include <iostream>

namespace launch {
	template <typename T>
	concept readable = requires(std::istream & is, T & x) {
		{ is >> x } -> std::same_as<std::istream&>;
	};
}