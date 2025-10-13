#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace launch {
	class hstr {
	private:
		std::string str;

	public:
		hstr() : str("") {}

		hstr(const char* _str) : str(_str) {}

		hstr(std::string _str) : str(_str) {}

		hstr& operator=(const char* _str);

		hstr& operator=(const std::string& _str);

		hstr& operator=(const hstr& _str);

		hstr& operator+=(const char* _str);

		hstr& operator+=(const std::string& _str);

		hstr& operator+=(const hstr& _str);

		hstr operator+(const char* _str) const;

		hstr operator+(const std::string& _str) const;

		hstr operator+(const hstr& _str) const;

		friend hstr operator+(const char* lhs, const hstr& rhs);

		friend hstr operator+(const std::string& lhs, const hstr& rhs);

		bool operator==(const hstr& _str) const;

		friend std::ostream& operator<<(std::ostream& out, const hstr& _str);

		friend std::istream& operator>>(std::istream& in, hstr& _str);

		std::string std_str() const;

		const char* c_str() const;

		std::string& raw();

		const std::string& raw_cr() const;

		size_t length() const;

		bool empty() const;
	};

	class lstr {
	private:
		std::wstring str;

	public:
		lstr() : str(L"") {}

		lstr(const wchar_t* _str) : str(_str) {}

		lstr(std::wstring _str) : str(_str) {}

		lstr& operator=(const wchar_t* _str);

		lstr& operator=(const std::wstring& _str);

		lstr& operator=(const lstr& _str);

		lstr& operator+=(const wchar_t* _str);

		lstr& operator+=(const std::wstring& _str);

		lstr& operator+=(const lstr& _str);

		lstr operator+(const wchar_t* _str) const;

		lstr operator+(const std::wstring& _str) const;

		lstr operator+(const lstr& _str) const;

		friend lstr operator+(const wchar_t* lhs, const lstr& rhs);

		friend lstr operator+(const std::wstring& lhs, const lstr& rhs);

		bool operator==(const lstr& _str) const;

		friend std::wostream& operator<<(std::wostream& wout, const lstr& _str);

		friend std::wistream& operator>>(std::wistream& win, lstr& _str);

		std::wstring std_str() const;

		const wchar_t* c_str() const;

		std::wstring& raw();

		const std::wstring& raw_cr() const;

		size_t length() const;

		bool empty() const;
	};

	std::vector<hstr> split(const hstr& orig, char delim);

	hstr concat(const std::vector<hstr>& list, const hstr& sep = "");

	hstr replace(hstr orig, const hstr& from, const hstr& to);

	void replace_inplace(hstr& orig, const hstr& from, const hstr& to);

	hstr trim(const hstr& orig);

	hstr ltrim(const hstr& orig);

	hstr rtrim(const hstr& orig);

	void trim_inplace(hstr& orig);

	void ltrim_inplace(hstr& orig);

	void rtrim_inplace(hstr& orig);

	std::vector<lstr> split(const lstr& orig, wchar_t delim);

	lstr concat(const std::vector<lstr>& list, const lstr& sep = L"");

	lstr replace(lstr orig, const lstr& from, const lstr& to);

	void replace_inplace(lstr& orig, const lstr& from, const lstr& to);

	lstr trim(const lstr& orig);

	lstr ltrim(const lstr& orig);

	lstr rtrim(const lstr& orig);

	void trim_inplace(lstr& orig);

	void ltrim_inplace(lstr& orig);

	void rtrim_inplace(lstr& orig);
}