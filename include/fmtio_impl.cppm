export module fmtio:impl;

#include "../include/launch_config.h"

import std;
import :concepts;

#if !defined(LAUNCH_NO_HEDGEHOG)
import hedgehog;
#endif

namespace launch {
#if !defined(LAUNCH_NO_HEDGEHOG)
	export void fmtout(const std::string& fmt, const hedgehog& cont = {}, bool raw = false, std::ostream& out = std::cout);

	export template <readable T>
	void fmtin_process(hedgehog& cont, std::istream& in) {
		T temp;
		in >> temp;
		cont.push_back(temp);
	}

	export template <readable... Ts>
	void fmtin(hedgehog& cont, std::istream& in = std::cin) {
		(fmtin_process<Ts>(cont, in), ...);
	}

	export template <readable T>
	void fmtin_single(T& x, std::istream& in = std::cin) {
		in >> x;
	}
#endif

	export void fmtin_line(std::string& str, std::istream& in = std::cin);
}