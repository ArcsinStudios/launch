#pragma once

#include <cstddef>

#define MACRO_MAJOR 14
#define MACRO_MINOR 3
#define _STRINGIFY(num) #num
#define STRINGIFY(num) _STRINGIFY(num)

namespace launch {
	constexpr size_t MAJOR = MACRO_MAJOR;
	constexpr size_t MINOR = MACRO_MINOR;
	constexpr const char* VERSION = "v1." STRINGIFY(MACRO_MAJOR) "." STRINGIFY(MACRO_MINOR);
}

#undef MACRO_MAJOR
#undef MACRO_MINOR
#undef _STRINGIFY
#undef STRINGIFY

/* vvv CUSTOMIZE THIS BEFORE USE! vvv */

#define LAUNCH_EXPERIMENTAL
#define LAUNCH_NO_THREAD_SAFE

/* ^^^ CUSTOMIZE THIS BEFORE USE! ^^^ */