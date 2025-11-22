#pragma once

#if !defined(LAUNCH_NO_HEDGEHOG)

#include <iostream>
#include <string>
#include <regex>

#include "hedgehog.h"

namespace launch {
	template <typename T>
	concept Readable = requires(std::istream& in, T& x) {
		{ in >> x } -> std::same_as<std::istream&>;
	};

	void fmtout(const std::string& fmt, const hedgehog& captures = {}, std::ostream& out = std::cout);

	template <Readable T>
	void fmtin_process(hedgehog& container, std::istream& in) {
		T temp;
		in >> temp;
		container.push_back(temp);
	}

	template <Readable... Args>
	void fmtin(hedgehog& container, std::istream& in = std::cin) {
		(fmtin_process<Args>(container, in), ...);
	}
}

#endif