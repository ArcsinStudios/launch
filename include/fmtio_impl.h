#pragma once

#if !defined(LAUNCH_NO_HEDGEHOG)

#include <format>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <string>

#include "hedgehog.h"
#include "fmtio_concepts.h"

namespace launch {
	void fmtout(const std::string& fmt, const hedgehog& hh = {}, bool raw = false, std::ostream& out = std::cout);

	template <readable T>
	void fmtin_process(hedgehog& hh, std::istream& in) {
		T temp;
		in >> temp;
		hh.push_back(temp);
	}

	template <readable... Ts>
	void fmtin(hedgehog& hh, std::istream& in = std::cin) {
		(fmtin_process<Ts>(hh, in), ...);
	}

	template <readable T>
	void fmtin_single(T& x, std::istream& in = std::cin) {
		in >> x;
	}

	void fmtin_line(std::string& str, std::istream& in = std::cin);
}

#endif