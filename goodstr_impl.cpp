#include "goodstr_impl.h"

namespace launch {
	hstr& hstr::operator=(const hstr& _str) {
		str = _str.str;
		return *this;
	}

	hstr& hstr::operator+=(const hstr& _str) {
		str += _str.str;
		return *this;
	}

	hstr hstr::operator+(const hstr& _str) const {
		hstr temp = *this;
		temp += _str;
		return temp;
	}

	bool hstr::operator==(const hstr& _str) const {
		return str == _str.str;
	}

	std::ostream& operator<<(std::ostream& out, const hstr& _str) {
		return out << _str.raw_cr();
	}

	std::istream& operator>>(std::istream& in, hstr& _str) {
		return in >> _str.raw();
	}

	std::string hstr::std_str() const {
		return str;
	}

	const char* hstr::c_str() const {
		return str.c_str();
	}

	std::string& hstr::raw() {
		return str;
	}

	const std::string& hstr::raw_cr() const {
		return str;
	}

	size_t hstr::length() const {
		return str.length();
	}

	bool hstr::empty() const {
		return str.empty();
	}

	lstr& lstr::operator=(const lstr& _str) {
		str = _str.str;
		return *this;
	}

	lstr& lstr::operator+=(const lstr& _str) {
		str += _str.str;
		return *this;
	}

	lstr lstr::operator+(const lstr& _str) const {
		lstr temp = *this;
		temp += _str;
		return temp;
	}

	bool lstr::operator==(const lstr& _str) const {
		return str == _str.str;
	}

	std::wostream& operator<<(std::wostream& wout, const lstr& _str) {
		return wout << _str.raw_cr();
	}

	std::wistream& operator>>(std::wistream& win, lstr& _str) {
		return win >> _str.raw();
	}

	std::wstring lstr::std_str() const {
		return str;
	}

	const wchar_t* lstr::c_str() const {
		return str.c_str();
	}

	std::wstring& lstr::raw() {
		return str;
	}

	const std::wstring& lstr::raw_cr() const {
		return str;
	}

	size_t lstr::length() const {
		return str.length();
	}

	bool lstr::empty() const {
		return str.empty();
	}

	std::vector<hstr> split(const hstr& orig, char delim) {
		std::vector<hstr> vec;
		std::stringstream ss(orig.std_str());
		std::string item;
		while (std::getline(ss, item, delim)) {
			vec.push_back(item);
		}
		return vec;
	}

	hstr concat(const std::vector<hstr>& list, const hstr& sep) {
		hstr str;
		size_t cnt = 0;
		size_t size = list.size();
		for (const hstr& item : list) {
			++cnt;
			str += item;
			if (!sep.empty() && cnt != size) {
				str += sep;
			}
		}
		return str;
	}

	hstr replace(hstr orig, const hstr& from, const hstr& to) {
		if (from == to) {
			return orig;
		}
		size_t pos = 0;
		while ((pos = orig.raw().find(from.raw_cr(), pos)) != std::string::npos) {
			orig.raw().replace(pos, from.length(), to.raw_cr());
			pos += to.length();
		}
		return orig;
	}

	void replace_inplace(hstr& orig, const hstr& from, const hstr& to) {
		orig = replace(orig, from, to);
	}

	hstr trim(const hstr& orig) {
		const char* ws = " \t\v\f\r\n";
		const size_t start = orig.raw_cr().find_first_not_of(ws);
		if (start == std::string::npos) {
			return "";
		}
		const size_t end = orig.raw_cr().find_last_not_of(ws);
		return orig.raw_cr().substr(start, (end - start + 1));
	}

	hstr ltrim(const hstr& orig) {
		const char* ws = " \t\v\f\r\n";
		const size_t start = orig.raw_cr().find_first_not_of(ws);
		if (start == std::string::npos) {
			return "";
		}
		return orig.raw_cr().substr(start);
	}

	hstr rtrim(const hstr& orig) {
		const char* ws = " \t\v\f\r\n";
		const size_t end = orig.raw_cr().find_last_not_of(ws);
		if (end == std::string::npos) {
			return "";
		}
		return orig.raw_cr().substr(0, end + 1);
	}

	void trim_inplace(hstr& orig) {
		orig = trim(orig);
	}

	void ltrim_inplace(hstr& orig) {
		orig = ltrim(orig);
	}

	void rtrim_inplace(hstr& orig) {
		orig = rtrim(orig);
	}

	std::vector<lstr> split(const lstr& orig, wchar_t delim) {
		std::vector<lstr> vec;
		std::wstringstream ss(orig.std_str());
		std::wstring item;
		while (std::getline(ss, item, delim)) {
			vec.push_back(item);
		}
		return vec;
	}

	lstr concat(const std::vector<lstr>& list, const lstr& sep) {
		lstr str = L"";
		size_t cnt = 0;
		size_t size = list.size();
		for (const lstr& item : list) {
			++cnt;
			str += item;
			if (!sep.empty() && cnt != size) {
				str += sep;
			}
		}
		return str;
	}

	lstr replace(lstr orig, const lstr& from, const lstr& to) {
		if (from == to) {
			return orig;
		}
		size_t pos = 0;
		while ((pos = orig.raw().find(from.raw_cr(), pos)) != std::string::npos) {
			orig.raw().replace(pos, from.length(), to.raw_cr());
			pos += to.length();
		}
		return orig;
	}

	void replace_inplace(lstr& orig, const lstr& from, const lstr& to) {
		orig = replace(orig, from, to);
	}

	lstr trim(const lstr& orig) {
		const wchar_t* ws = L" \t\v\f\r\n";
		const size_t start = orig.raw_cr().find_first_not_of(ws);
		if (start == std::string::npos) {
			return L"";
		}
		const size_t end = orig.raw_cr().find_last_not_of(ws);
		return orig.raw_cr().substr(start, (end - start + 1));
	}

	lstr ltrim(const lstr& orig) {
		const wchar_t* ws = L" \t\v\f\r\n";
		const size_t start = orig.raw_cr().find_first_not_of(ws);
		if (start == std::string::npos) {
			return L"";
		}
		return orig.raw_cr().substr(start);
	}

	lstr rtrim(const lstr& orig) {
		const wchar_t* ws = L" \t\v\f\r\n";
		const size_t end = orig.raw_cr().find_last_not_of(ws);
		if (end == std::string::npos) {
			return L"";
		}
		return orig.raw_cr().substr(0, end + 1);
	}

	void trim_inplace(lstr& orig) {
		orig = trim(orig);
	}

	void ltrim_inplace(lstr& orig) {
		orig = ltrim(orig);
	}

	void rtrim_inplace(lstr& orig) {
		orig = rtrim(orig);
	}
}