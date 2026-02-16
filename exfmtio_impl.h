#pragma once

#if !defined(LAUNCH_NO_HEDGEHOG)
#include "hedgehog.h"
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

#if !defined(LAUNCH_NO_HEDGEHOG)
	template <typename T>
	bool fmtin_deduce_process(launch::hedgehog_elemproxy& proxy, const std::string& str) {
		T temp;
		std::stringstream ss(str);
		ss >> std::boolalpha >> temp;
		if (ss.fail() || !ss.eof()) {
			return false;
		}
		proxy = temp;
		return true;
	}

	template <typename... Candidates>
	void fmtin_deduce_single(launch::hedgehog_elemproxy& proxy, std::istream& in = std::cin) {
		bool last_state = false;
		std::string str;
		in >> str;
		((last_state ? 0 : last_state = fmtin_deduce_process<Candidates>(proxy, str)), ...);
		if (!last_state) {
			proxy = str;
		}
	}

	template <typename... Candidates>
	void fmtin_deduce(launch::hedgehog& hh, size_t count = 1, std::istream& in = std::cin) {
		for (size_t i = 0; i < count; ++i) {
			hh.push_back(0);
			fmtin_deduce_single<Candidates...>(hh[i], in);
		}
	}

	void fmtin_deduce_auto(launch::hedgehog& hh, size_t count = 1, std::istream& in = std::cin);
#endif

	extern nullstream nullout;
}