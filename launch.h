#pragma once

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

namespace launch {
	constexpr uint32_t EASTER_EGG = 0x8B0BA7EA;
}