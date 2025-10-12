#pragma once

#if !defined(LAUNCH_NO_HEDGEHOG)

#include <any>
#include <iostream>
#include <string>
#include <regex>

#include "hedgehog.h"

namespace launch {
	template <typename T>
	concept Inputtable = requires(std::istream& in, T& x) {
		{ in >> x } -> std::same_as<std::istream&>;
	};

	void fmtout(const std::string& fmt, const hedgehog& captures = {}, std::ostream& out = std::cout);

	template <Inputtable T>
	void fmtin_process(hedgehog& container, std::istream& in) {
		T temp;
		in >> temp;
		container.stick(temp);
	}

	template <Inputtable... Args>
	void fmtin(hedgehog& container, std::istream& in = std::cin) {
		(fmtin_process<Args>(container, in), ...);
	}
}

#endif