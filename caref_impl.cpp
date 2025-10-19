#include "caref_impl.h"

namespace launch {
	const char* uaf_error::what() const noexcept {
		return std::runtime_error::what();
	}
}