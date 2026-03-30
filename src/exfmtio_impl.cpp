#include "../include/launch_config.h"

#include "../include/exfmtio_impl.h"

namespace leisure {
	int nullbuf::overflow(int c) {
		return c;
	}

#if !defined(LAUNCH_NO_HEDGEHOG)
	template <>
	bool fmtin_deduce_process<char>(launch::hedgehog& cont, const std::string& str, std::ios_base::fmtflags in_flags) {
		if (str.length() > 1) {
			return false;
		}
		cont.push_back(str[0]);
		return true;
	}

	void fmtin_deduce_auto(launch::hedgehog& cont, size_t count, std::istream& in) {
		fmtin_deduce<int, long long, unsigned long long, double, char, bool>(cont, count, in);
	}
#endif

	nullstream nullout;
}