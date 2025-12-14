#pragma once

#include <ostream>
#include <streambuf>

namespace launch {
	class nullbuf : public std::streambuf {
	public:
		int overflow(int c) override;
	};

	class nullstream : public std::ostream {
	private:
		nullbuf buffer;

	public:
		nullstream() : std::ostream(&buffer) {}
	};

	extern nullstream nullout;
}