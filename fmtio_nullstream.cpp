#include "launch_config.h"

#include "fmtio_nullstream.h"

namespace launch {
	int nullbuf::overflow(int c) {
		return c;
	}

	nullstream nullout;
}