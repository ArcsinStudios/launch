#pragma once

#include <format>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <string>

#if !defined(LAUNCH_NO_HEDGEHOG)
#include "hedgehog.h"
#endif

#include "fmtio_concepts.h"

namespace launch {
#if !defined(LAUNCH_NO_HEDGEHOG)
	void fmtout(const std::string& fmt, const hedgehog& cont = {}, bool raw = false, std::ostream& out = std::cout);

	template <readable T>
	void fmtin_process(hedgehog& cont, std::istream& in) {
		T temp;
		in >> temp;
		cont.push_back(temp);
	}

	template <readable... Ts>
	void fmtin(hedgehog& cont, std::istream& in = std::cin) {
		(fmtin_process<Ts>(cont, in), ...);
	}

	template <readable T>
	void fmtin_single(T& x, std::istream& in = std::cin) {
		in >> x;
	}
#endif

	void fmtin_line(std::string& str, std::istream& in = std::cin);
}