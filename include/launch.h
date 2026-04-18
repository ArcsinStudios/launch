#pragma once

#include <cstddef>

#define MACRO_MAJOR 15
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

#include "launch_config.h"

#if !defined(LAUNCH_NO_CHROYES)
#include "chroyes.h"
#endif

#if !defined(LAUNCH_NO_CLAP)
#include "clap.h"
#endif

#if !defined(LAUNCH_NO_ESCSEQ)
#include "escseq.h"
#endif

#if !defined(LAUNCH_NO_FMTIO)
#include "fmtio.h"
#endif

#if !defined(LAUNCH_NO_HEDGEHOG)
#include "hedgehog.h"
#endif

#if !defined(LAUNCH_NO_GOODMATH)
#include "goodmath.h"
#endif

#if !defined(LAUNCH_NO_GOODRAND)
#include "goodrand.h"
#endif

#if !defined(LAUNCH_NO_GOODSTR)
#include "goodstr.h"
#endif

#if defined(LAUNCH_EXPERIMENTAL)
#include "leisure.h"
#endif