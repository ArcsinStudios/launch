export module fmtio:concepts;

import std;

namespace launch {
	export template <typename T>
	concept readable = requires(std::istream& in, T& x) {
		{ in >> x } -> std::same_as<std::istream&>;
	};
}