#include "launch_config.h"

#include "fmtio_impl.h"

#if !defined(LAUNCH_NO_HEDGEHOG)

namespace launch {
	void fmtout(const std::string& fmt, const hedgehog& captures, std::ostream& out) {
		if (fmt.find('{') == std::string::npos && fmt.find('}') == std::string::npos) {
			out << fmt;
			return;
		}
		std::stringstream ss;
		ss.flags(out.flags());
		size_t fmt_length = fmt.length();
		size_t captures_size = captures.size();
		bool auto_indexing = false;
		size_t curr_index = 0;
		for (size_t i = 0; i < fmt_length; ++i) {
			switch (fmt[i]) {
			case '{':
				if (i + 1 == fmt_length) {
					throw std::runtime_error("fmtout: unmatched {");
				}
				if (fmt[i + 1] == '{') {
					ss << '{';
					++i;
				}
				else {
					++i;
					size_t index;
					if (fmt[i] == '}') {
						if (!curr_index) {
							auto_indexing = true;
						}
						if (auto_indexing) {
							index = curr_index++;
						}
						else {
							throw std::runtime_error("fmtout: cannot mix manual and automatic indexing");
						}
					}
					else {
						if (auto_indexing) {
							throw std::runtime_error("fmtout: cannot mix manual and automatic indexing");
						}
						std::string index_str;
						for (; fmt[i] != '}'; ++i) {
							if (i + 1 == fmt_length) {
								throw std::runtime_error("fmtout: unmatched {");
							}
							if (fmt[i] < '0' || fmt[i] > '9') {
								throw std::runtime_error(std::string("fmtout: expected a digit but got ") + fmt[i]);
							}
							index_str += fmt[i];
						}
						index = std::stoull(index_str);
						if (index >= captures_size) {
							throw std::runtime_error(
								"fmtout: index (which is " +
								index_str +
								") >= captures.size() (which is " +
								std::to_string(captures_size) +
								")"
							);
						}
					}
					ss << captures[index];
				}
				break;
			case '}':
				if (i + 1 != fmt_length && fmt[i + 1] == '}') {
					ss << '}';
					++i;
				}
				else {
					throw std::runtime_error("fmtout: unmatched }");
				}
				break;
			default:
				ss << fmt[i];
			}
		}
		out << ss.str();
	}
}

#endif