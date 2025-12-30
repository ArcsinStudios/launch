#include "goodstr_impl.h"

namespace launch {
	std::vector<std::string> split(const std::string& orig, char delim) {
		std::vector<std::string> vec;
		std::stringstream ss(orig);
		std::string item;
		while (std::getline(ss, item, delim)) {
			vec.push_back(item);
		}
		return vec;
	}

	std::string concat(const std::vector<std::string>& list, const std::string& sep) {
		std::string str;
		size_t cnt = 0;
		size_t size = list.size();
		for (const std::string& item : list) {
			++cnt;
			str += item;
			if (!sep.empty() && cnt != size) {
				str += sep;
			}
		}
		return str;
	}

	std::string replace(std::string orig, const std::string& from, const std::string& to) {
		if (from == to) {
			return orig;
		}
		size_t pos = 0;
		while ((pos = orig.find(from, pos)) != std::string::npos) {
			orig.replace(pos, from.length(), to);
			pos += to.length();
		}
		return orig;
	}

	void replace_inplace(std::string& orig, const std::string& from, const std::string& to) {
		orig = replace(orig, from, to);
	}

	std::string trim(const std::string& orig) {
		const char* ws = " \t\v\f\r\n";
		const size_t start = orig.find_first_not_of(ws);
		if (start == std::string::npos) {
			return "";
		}
		const size_t end = orig.find_last_not_of(ws);
		return orig.substr(start, (end - start + 1));
	}

	std::string ltrim(const std::string& orig) {
		const char* ws = " \t\v\f\r\n";
		const size_t start = orig.find_first_not_of(ws);
		if (start == std::string::npos) {
			return "";
		}
		return orig.substr(start);
	}

	std::string rtrim(const std::string& orig) {
		const char* ws = " \t\v\f\r\n";
		const size_t end = orig.find_last_not_of(ws);
		if (end == std::string::npos) {
			return "";
		}
		return orig.substr(0, end + 1);
	}

	void trim_inplace(std::string& orig) {
		orig = trim(orig);
	}

	void ltrim_inplace(std::string& orig) {
		orig = ltrim(orig);
	}

	void rtrim_inplace(std::string& orig) {
		orig = rtrim(orig);
	}
}