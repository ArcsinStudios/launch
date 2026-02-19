#pragma once

#if !defined(LAUNCH_NO_HEDGEHOG)

#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

#include "hedgehog.h"
#include "fmtio_concepts.h"

namespace launch {

	void fmtout(const std::string& fmt, const hedgehog& captures = {}, std::ostream& out = std::cout);

	template <readable T>
	void fmtin_process(hedgehog& container, std::istream& in) {
		T temp;
		in >> temp;
		container.push_back(temp);
	}

	template <readable... Ts>
	void fmtin(hedgehog& container, std::istream& in = std::cin) {
		(fmtin_process<Ts>(container, in), ...);
	}
}

#endif