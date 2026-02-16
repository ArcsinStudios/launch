#include "launch_config.h"

#include "exfmtio_impl.h"

namespace leisure {
	int nullbuf::overflow(int c) {
		return c;
	}

#if !defined(LAUNCH_NO_HEDGEHOG)
	void fmtin_deduce_auto(launch::hedgehog& hh, size_t count, std::istream& in) {
		fmtin_deduce<int, long long, unsigned long long, double, bool>(hh, count, in);
	}
#endif

	nullstream nullout;
}