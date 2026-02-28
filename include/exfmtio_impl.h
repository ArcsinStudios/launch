#pragma once

#if !defined(LAUNCH_NO_HEDGEHOG) && !defined(LAUNCH_NO_FMTIO)
#include "hedgehog.h"
#include "fmtio.h"
#include <iostream>
#include <sstream>
#endif

#include <ostream>
#include <streambuf>

namespace leisure {
	class nullbuf : public std::streambuf {
	public:
		int overflow(int c) override;
	};

	class nullstream : public std::ostream {
	private:
		nullbuf buffer;

	public:
		nullstream() : std::ostream(&buffer) {}
	};

#if !defined(LAUNCH_NO_HEDGEHOG) && !defined(LAUNCH_NO_FMTIO)
	template <launch::readable T>
	bool fmtin_deduce_process(launch::hedgehog& hh, const std::string& str, std::ios_base::fmtflags in_flags) {
		T temp;
		std::stringstream ss(str);
		ss.flags(in_flags);
		ss >> temp;
		if (ss.fail() || !ss.eof()) {
			return false;
		}
		hh.push_back(temp);
		return true;
	}

	template <>
	bool fmtin_deduce_process<char>(launch::hedgehog& hh, const std::string& str, std::ios_base::fmtflags in_flags);

	template <launch::readable... Ts>
	void fmtin_deduce_single(launch::hedgehog& hh, std::istream& in = std::cin) {
		bool last_state = false;
		std::string str;
		in >> str;
		((last_state ? 0 : last_state = fmtin_deduce_process<Ts>(hh, str, in.flags())), ...);
		if (!last_state) {
			hh.push_back(str);
		}
	}

	template <launch::readable... Ts>
	void fmtin_deduce(launch::hedgehog& hh, size_t count = 1, std::istream& in = std::cin) {
		for (size_t i = 0; i < count; ++i) {
			fmtin_deduce_single<Ts...>(hh, in);
		}
	}

	void fmtin_deduce_auto(launch::hedgehog& hh, size_t count = 1, std::istream& in = std::cin);
#endif

	extern nullstream nullout;
}