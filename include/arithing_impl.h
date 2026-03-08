#pragma once

#include <compare>
#include <iostream>
#include <istream>
#include <limits>
#include <numeric>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

namespace leisure {
	enum class arint_specval : unsigned char {
		nop = 0b0000,
		neg = 0b0001,
		nan = 0b0010,
		inf = 0b0100
	};

	constexpr arint_specval operator|(arint_specval lhs, arint_specval rhs);
	constexpr arint_specval operator&(arint_specval lhs, arint_specval rhs);

	class arreal;

	class arint {
	private:
		unsigned long long value;
		bool sign;
		bool nan;
		bool inf;

	public:
		friend class arreal;

		constexpr arint(unsigned long long _value = 0, arint_specval specval = arint_specval::nop) :
			value(_value),
			sign(!static_cast<bool>(specval & arint_specval::neg)),
			nan(static_cast<bool>(specval & arint_specval::nan)),
			inf(static_cast<bool>(specval & arint_specval::inf))
		{}

		arint& operator+=(const arint& other);

		arint& operator-=(const arint& other);

		arint& operator*=(const arint& other);

		arint& operator/=(const arint& other);

		arint& operator^=(const arint& other);

		arint& operator%=(const arint& other);

		arint& operator++();

		arint operator++(int);

		arint& operator--();

		arint operator--(int);

		arint operator+() const;

		arint operator-() const;

		friend std::partial_ordering operator<=>(const arint& a, const arint& b);

		friend bool operator==(const arint& a, const arint& b);

		friend std::ostream& operator<<(std::ostream& out, const arint& val);

		friend std::istream& operator>>(std::istream& in, arint& val);

		friend std::partial_ordering operator<=>(const arreal& a, const arreal& b);

		friend bool operator==(const arreal& a, const arreal& b);

		friend std::string to_decimal(const arreal& val);
	};

	arint operator+(const arint& a, const arint& b);

	arint operator-(const arint& a, const arint& b);

	arint operator*(const arint& a, const arint& b);

	arint operator/(const arint& a, const arint& b);

	arint operator^(const arint& a, const arint& b);

	arint operator%(const arint& a, const arint& b);

	class arreal {
	private:
		arint num;
		arint den;

		constexpr void adjust();

	public:
		constexpr arreal(const arint& _num = 0, const arint& _den = 1);

		arreal& operator+=(const arreal& other);

		arreal& operator-=(const arreal& other);

		arreal& operator*=(const arreal& other);

		arreal& operator/=(const arreal& other);

		arreal& operator%=(const arreal& other);

		arreal operator+() const;

		arreal operator-() const;

		friend std::partial_ordering operator<=>(const arreal& a, const arreal& b);

		friend bool operator==(const arreal& a, const arreal& b);

		friend std::ostream& operator<<(std::ostream& out, const arreal& val);

		friend std::istream& operator>>(std::istream& in, arreal& val);

		friend std::string to_decimal(const arreal& val);
	};

	arreal operator+(const arreal& a, const arreal& b);

	arreal operator-(const arreal& a, const arreal& b);

	arreal operator*(const arreal& a, const arreal& b);

	arreal operator/(const arreal& a, const arreal& b);

	arreal operator%(const arreal& a, const arreal& b);
}