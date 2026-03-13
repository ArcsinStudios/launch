#pragma once

#include <cstddef>

#define MACRO_MAJOR 14
#define MACRO_MINOR 4
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

/*                   CUSTOMIZE THIS BEFORE USE!                   */
/* vvv THE DEFAULT DEFINITIONS ARE FOR TESTING PURPOSES ONLY! vvv */

#define LAUNCH_EXPERIMENTAL
#define LAUNCH_NO_THREAD_SAFE

/* ^^^ THE DEFAULT DEFINITIONS ARE FOR TESTING PURPOSES ONLY! ^^^ */
/*                   CUSTOMIZE THIS BEFORE USE!                   */