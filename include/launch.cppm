export module launch;

#include "launch_config.h"

import std;

#define MACRO_MAJOR 16
#define MACRO_MINOR 1
#define _STRINGIFY(num) #num
#define STRINGIFY(num) _STRINGIFY(num)

namespace launch {
	export constexpr size_t MAJOR = MACRO_MAJOR;
	export constexpr size_t MINOR = MACRO_MINOR;
	export constexpr const char* VERSION = "v1." STRINGIFY(MACRO_MAJOR) "." STRINGIFY(MACRO_MINOR) " (lts-modules)";
}

#undef MACRO_MAJOR
#undef MACRO_MINOR
#undef _STRINGIFY
#undef STRINGIFY

#if !defined(LAUNCH_NO_CHROYES)
export import chroyes;
#endif

#if !defined(LAUNCH_NO_CLAP)
export import clap;
#endif

#if !defined(LAUNCH_NO_ESCSEQ)
export import escseq;
#endif

#if !defined(LAUNCH_NO_FMTIO)
export import fmtio;
#endif

#if !defined(LAUNCH_NO_HEDGEHOG)
export import hedgehog;
#endif

#if !defined(LAUNCH_NO_GOODMATH)
export import goodmath;
#endif

#if !defined(LAUNCH_NO_GOODRAND)
export import goodrand;
#endif

#if !defined(LAUNCH_NO_GOODSTR)
export import goodstr;
#endif

#if defined(LAUNCH_EXPERIMENTAL)
export import leisure;
#endif