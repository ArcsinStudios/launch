#include "../include/launch_config.h"

#include "../include/fmtio_impl.h"

#if !defined(LAUNCH_NO_HEDGEHOG)

namespace launch {
	void fmtout(const std::string& fmt, const hedgehog& hh, bool raw, std::ostream& out) {
		if (raw || fmt.find_first_of("{}[]|") == std::string::npos) {
			out << fmt;
			return;
		}
		std::stringstream ss;
		ss.flags(out.flags());
		size_t fmt_length = fmt.length();
		size_t hh_size = hh.size();
		bool auto_indexing = false;
		size_t curr_index = 0;
		bool brackets = false;
		for (size_t i = 0; i < fmt_length; ++i) {
			switch (fmt[i]) {
			case '{':
				if (i + 1 == fmt_length) {
					throw std::format_error("fmtout: unmatched { at index " + std::to_string(i));
				}
				if (fmt[i + 1] == '{') {
					++i;
					ss << '{';
					break;
				}
				if (brackets) {
					throw std::format_error("fmtout: unexpected { at index " + std::to_string(i));
				}
				++i;
				{
					size_t index;
					if (fmt[i] == '}') {
						if (!curr_index) {
							auto_indexing = true;
						}
						if (auto_indexing) {
							index = curr_index++;
						}
						else {
							throw std::format_error("fmtout: unexpected } at index " + std::to_string(i));
						}
					}
					else {
						if (auto_indexing) {
							throw std::format_error(
								std::string("fmtout: expected } but got ") +
								fmt[i] +
								" at index " +
								std::to_string(i)
							);
						}
						std::string index_str;
						for (; fmt[i] != '}'; ++i) {
							if (i + 1 == fmt_length) {
								throw std::format_error("fmtout: unmatched { at index " + std::to_string(i));
							}
							if (fmt[i] < '0' || fmt[i] > '9') {
								throw std::format_error(
									std::string("fmtout: expected a digit but got ") +
									fmt[i] +
									" at index " +
									std::to_string(i)
								);
							}
							index_str += fmt[i];
						}
						index = std::stoull(index_str);
						if (index >= hh_size) {
							throw std::format_error(
								"fmtout: index (which is " +
								index_str +
								") >= hh.size() (which is " +
								std::to_string(hh_size) +
								")"
							);
						}
					}
					ss << hh[index];
				}
				break;
			case '}':
				if (i + 1 != fmt_length && fmt[i + 1] == '}') {
					++i;
					ss << '}';
					break;
				}
				throw std::format_error("fmtout: unmatched } at index " + std::to_string(i));
			case '[':
				if (i + 1 == fmt_length) {
					throw std::format_error("fmtout: unmatched [ at index " + std::to_string(i));
				}
				if (fmt[i + 1] == '[') {
					++i;
					ss << '[';
					break;
				}
				if (brackets) {
					throw std::format_error("fmtout: unexpected [ at index " + std::to_string(i));
				}
				brackets = true;
				++i;
				{
					std::string sep;
					for (; fmt[i] != ']' || i + 1 != fmt_length && fmt[i] == ']' && fmt[i + 1] == ']'; ++i) {
						if (i + 1 == fmt_length) {
							throw std::format_error("fmtout: unmatched [ at index " + std::to_string(i));
						}
						switch (fmt[i]) {
						case '[':
							if (fmt[i + 1] != '[') {
								throw std::format_error("fmtout: unexpected [ at index " + std::to_string(i));
							}
							++i;
							sep += '[';
							break;
						case ']':
							if (fmt[i + 1] == ']') {
								++i;
								sep += ']';
							}
							break;
						case '|':
							if (i + 1 != fmt_length && fmt[i + 1] == '|') {
								++i;
								sep += '|';
							}
							break;
						default:
							sep += fmt[i];
						}
					}
					for (size_t i = 0; i < hh_size; ++i) {
						ss << hh[i];
						if (i + 1 != hh_size) {
							ss << sep;
						}
					}
				}
				break;
			case ']':
				if (i + 1 != fmt_length && fmt[i + 1] == ']') {
					ss << ']';
					++i;
					break;
				}
				throw std::format_error("fmtout: unmatched ] at index " + std::to_string(i));
			case '|':
				if (i + 1 != fmt_length && fmt[i + 1] == '|') {
					++i;
					ss << '|';
				}
				break;
			default:
				ss << fmt[i];
			}
		}
		out << ss.str();
	}

	void fmtin_line(std::string& str, std::istream& in) {
		std::getline(in >> std::ws, str);
	}
}

#endif