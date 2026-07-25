export module exfmtio:impl;

#include "../include/launch_config.h"

import std;

#if !defined(LAUNCH_NO_HEDGEHOG) && !defined(LAUNCH_NO_FMTIO)
import hedgehog;
import fmtio;
#endif

namespace leisure {
	export class nullbuf : public std::streambuf {
	public:
		int overflow(int c) override;
	};

	export class nullstream : public std::ostream {
	private:
		nullbuf buffer;

	public:
		nullstream() : std::ostream(&buffer) {}
	};

#if !defined(LAUNCH_NO_HEDGEHOG) && !defined(LAUNCH_NO_FMTIO)
	export template <launch::readable T>
	bool fmtin_deduce_process(launch::hedgehog& cont, const std::string& str, std::ios_base::fmtflags in_flags) {
		T temp;
		std::stringstream ss(str);
		ss.flags(in_flags);
		ss >> temp;
		if (ss.fail() || !ss.eof()) {
			return false;
		}
		cont.push_back(temp);
		return true;
	}

	template <>
	bool fmtin_deduce_process<char>(launch::hedgehog& cont, const std::string& str, std::ios_base::fmtflags in_flags);

	export template <launch::readable... Ts>
	void fmtin_deduce_single(launch::hedgehog& cont, std::istream& in = std::cin) {
		bool last_state = false;
		std::string str;
		in >> str;
		((last_state ? 0 : last_state = fmtin_deduce_process<Ts>(cont, str, in.flags())), ...);
		if (!last_state) {
			cont.push_back(str);
		}
	}

	export template <launch::readable... Ts>
	void fmtin_deduce(launch::hedgehog& cont, size_t count = 1, std::istream& in = std::cin) {
		for (size_t i = 0; i < count; ++i) {
			fmtin_deduce_single<Ts...>(cont, in);
		}
	}

	export void fmtin_deduce_auto(launch::hedgehog& cont, size_t count = 1, std::istream& in = std::cin);
#endif

	export extern nullstream nullout;
}