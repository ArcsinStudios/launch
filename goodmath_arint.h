#pragma once

#include <algorithm>
#include <compare>
#include <iostream>
#include <istream>
#include <limits>
#include <string>
#include <type_traits>

namespace launch {
	enum class arint_specval : unsigned char {
		nop = 0b0000,
		neg = 0b0001,
		nan = 0b0010,
		inf = 0b0100
	};

	constexpr arint_specval operator|(arint_specval lhs, arint_specval rhs);
	constexpr arint_specval operator&(arint_specval lhs, arint_specval rhs);

	class arint {
	private:
		unsigned long long value;
		bool sign;
		bool nan;
		bool inf;

	public:
		constexpr arint(unsigned long long _value = 0, arint_specval specval = arint_specval::nop) :
			value(_value),
			sign(!static_cast<bool>(specval & arint_specval::neg)),
			nan(static_cast<bool>(specval & arint_specval::nan)),
			inf(static_cast<bool>(specval & arint_specval::inf))
		{}

		arint& operator=(const arint& other) = default;

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

		arint operator+(const arint& other) const;

		arint operator-(const arint& other) const;

		arint operator*(const arint& other) const;

		arint operator/(const arint& other) const;

		arint operator^(const arint& other) const;

		arint operator%(const arint& other) const;

		arint operator+() const;

		arint operator-() const;

		std::partial_ordering operator<=>(const arint& other) const;

		bool operator==(const arint& other) const;

		arint operator[](const arint& digit) const;

		friend std::ostream& operator<<(std::ostream& out, const arint& val);

		friend std::istream& operator>>(std::istream& in, arint& val);
	};
}

namespace std {
	template <>
	struct numeric_limits<launch::arint> {
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = true;
		static constexpr bool has_quiet_NaN = true;
		static constexpr bool has_signaling_NaN = false;
		static constexpr std::float_denorm_style has_denorm = std::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr std::float_round_style round_style = std::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = false;
		static constexpr int digits = 64;
		static constexpr int digits10 = 19;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = false;
		static constexpr bool tinyness_before = false;

		static constexpr launch::arint min() {
			return launch::arint(numeric_limits<unsigned long long>::max(), launch::arint_specval::neg);
		}

		static constexpr launch::arint lowest() {
			return min();
		}

		static constexpr launch::arint max() {
			return numeric_limits<unsigned long long>::max();
		}

		static constexpr launch::arint epsilon() {
			return 0;
		}

		static constexpr launch::arint round_error() {
			return 0;
		}

		static constexpr launch::arint infinity() {
			return launch::arint(0, launch::arint_specval::inf);
		}

		static constexpr launch::arint quiet_NaN() {
			return launch::arint(0, launch::arint_specval::nan);
		}

		static constexpr launch::arint signaling_NaN() {
			return 0;
		}

		static constexpr launch::arint denorm_min() {
			return 0;
		}
	};
}