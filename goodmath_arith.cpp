#include "launch_config.h"

#include "goodmath_arith.h"

namespace launch {
	constexpr arint_specval operator|(arint_specval lhs, arint_specval rhs) {
		return static_cast<arint_specval>(
			static_cast<std::underlying_type_t<arint_specval>>(lhs) |
			static_cast<std::underlying_type_t<arint_specval>>(rhs)
		);
	}
	constexpr arint_specval operator&(arint_specval lhs, arint_specval rhs) {
		return static_cast<arint_specval>(
			static_cast<std::underlying_type_t<arint_specval>>(lhs) &
			static_cast<std::underlying_type_t<arint_specval>>(rhs)
		);
	}

	arint& arint::operator+=(const arint& other) {
		if (nan || inf || other.nan || other.inf) {
			nan = nan || other.nan || (inf && other.inf && (sign != other.sign));
			inf = !nan && (inf || other.inf);
			sign = other.inf ? other.sign : sign;
			return *this;
		}
		if (sign == other.sign) {
			if (value > std::numeric_limits<unsigned long long>::max() - other.value) {
				inf = true;
				return *this;
			}
			value += other.value;
		}
		else {
			if (value < other.value) {
				sign = !sign;
			}
			value = std::max(value, other.value) - std::min(value, other.value);
		}
		return *this;
	}

	arint& arint::operator-=(const arint& other) {
		*this += -other;
		return *this;
	}

	arint& arint::operator*=(const arint& other) {
		sign = sign == other.sign;
		if (nan || inf || other.nan || other.inf) {
			nan = nan || other.nan || (inf && !other.value) || (!value && other.inf);
			inf = !nan && (inf || other.inf);
			return *this;
		}
		if (value > std::numeric_limits<unsigned long long>::max() / other.value) {
			inf = true;
			return *this;
		}
		value *= other.value;
		return *this;
	}

	arint& arint::operator/=(const arint& other) {
		sign = sign == other.sign;
		if (!other.value || nan || inf || other.nan || other.inf) {
			nan = nan || other.nan || (inf && other.inf) || (!value && !other.value);
			inf = !nan && (inf || (value && !other.value));
			value = (!nan && !inf && other.inf) ? 0 : value;
			return *this;
		}
		value /= other.value;
		return *this;
	}

	arint& arint::operator^=(const arint& other) {
		arint p = 1;
		for (arint i = 0; i < other; ++i) {
			p *= *this;
		}
		*this = p;
		return *this;
	}

	arint& arint::operator%=(const arint& other) {
		value %= other.value;
		return *this;
	}

	arint& arint::operator++() {
		*this += 1;
		return *this;
	}

	arint arint::operator++(int) {
		arint temp = *this;
		*this += 1;
		return temp;
	}

	arint& arint::operator--() {
		*this -= 1;
		return *this;
	}

	arint arint::operator--(int) {
		arint temp = *this;
		*this -= 1;
		return temp;
	}

	arint arint::operator+(const arint& other) const {
		arint temp = *this;
		temp += other;
		return temp;
	}

	arint arint::operator-(const arint& other) const {
		arint temp = *this;
		temp -= other;
		return temp;
	}

	arint arint::operator*(const arint& other) const {
		arint temp = *this;
		temp *= other;
		return temp;
	}

	arint arint::operator/(const arint& other) const {
		arint temp = *this;
		temp /= other;
		return temp;
	}

	arint arint::operator^(const arint& other) const {
		arint temp = *this;
		temp ^= other;
		return temp;
	}

	arint arint::operator%(const arint& other) const {
		arint temp = *this;
		temp %= other;
		return temp;
	}

	arint arint::operator+() const {
		return *this;
	}

	arint arint::operator-() const {
		return arint(value, sign ? arint_specval::neg : arint_specval::nop);
	}

	std::partial_ordering arint::operator<=>(const arint& other) const {
		if (nan || other.nan) {
			return std::partial_ordering::unordered;
		}
		if (sign != other.sign) {
			return sign ? std::strong_ordering::greater : std::strong_ordering::less;
		}
		if (sign) {
			if (inf && !other.inf) {
				return std::strong_ordering::greater;
			}
			if (!inf && other.inf) {
				return std::strong_ordering::less;
			}
			return value <=> other.value;
		}
		else {
			if (inf && !other.inf) {
				return std::strong_ordering::less;
			}
			if (!inf && other.inf) {
				return std::strong_ordering::greater;
			}
			return other.value <=> value;
		}
	}

	bool arint::operator==(const arint& other) const {
		return *this <=> other == 0;
	}

	arint arint::operator[](const arint& digit) const {
		if (digit > std::numeric_limits<unsigned long long>::digits10) {
			return 0;
		}
		return (*this / (arint(10) ^ digit) % 10).value;
	}

	std::ostream& operator<<(std::ostream& out, const arint& val) {
		if (val.nan) {
			return out << "NaN";
		}
		if (!val.sign) {
			out << "-";
		}
		if (val.inf) {
			return out << "inf";
		}
		return out << val.value;
	}

	std::istream& operator>>(std::istream& in, arint& val) {
		std::string s_value;
		in >> s_value;
		unsigned long long value = 0;
		arint_specval attr = arint_specval::nop;
		if (s_value == "NaN") {
			attr = attr | arint_specval::nan;
		}
		else {
			switch (s_value[0]) {
			case '-':
				attr = attr | arint_specval::neg;
			case '+':
				s_value = s_value.substr(1);
			}
			if (s_value == "inf") {
				attr = attr | arint_specval::inf;
			}
			else {
				try {
					value = std::stoull(s_value);
				}
				catch (const std::out_of_range&) {
					attr = attr | arint_specval::inf;
				}
			}
		}
		val = arint(value, attr);
		return in;
	}

	constexpr void arreal::_Adjust() {
		unsigned long long nd_gcd = std::gcd(num.value, den.value);
		num.value /= nd_gcd;
		den.value /= nd_gcd;
		if (num.sign && !den.sign) {
			num.sign = false;
			den.sign = true;
		}
		if (num.sign == den.sign) {
			num.sign = true;
			den.sign = true;
		}
	}

	constexpr arreal::arreal(const arint& _num, const arint& _den) : num(_num), den(_den) {
		_Adjust();
	}

	arreal& arreal::operator+=(const arreal& other) {
		if (den == other.den) {
			num += other.num;
		}
		else {
			unsigned long long den_lcm = std::lcm(den.value, other.den.value);
			num = num * (den_lcm / den.value) + other.num * (den_lcm / other.den.value);
			den.value = den_lcm;
		}
		_Adjust();
		return *this;
	}

	arreal& arreal::operator-=(const arreal& other) {
		*this += -other;
		return *this;
	}

	arreal& arreal::operator*=(const arreal& other) {
		num *= other.num;
		den *= other.den;
		_Adjust();
		return *this;
	}

	arreal& arreal::operator/=(const arreal& other) {
		arreal temp(other.den, other.num);
		*this *= temp;
		return *this;
	}

	arreal arreal::operator+(const arreal& other) const {
		arreal temp = *this;
		temp += other;
		return temp;
	}

	arreal arreal::operator-(const arreal& other) const {
		arreal temp = *this;
		temp -= other;
		return temp;
	}

	arreal arreal::operator*(const arreal& other) const {
		arreal temp = *this;
		temp *= other;
		return temp;
	}

	arreal arreal::operator/(const arreal& other) const {
		arreal temp = *this;
		temp /= other;
		return temp;
	}

	arreal arreal::operator+() const {
		return *this;
	}

	arreal arreal::operator-() const {
		return arreal(-num, den);
	}

	std::partial_ordering arreal::operator<=>(const arreal& other) const {
		unsigned long long den_lcm = std::lcm(den.value, other.den.value);
		return num * (den_lcm / den.value) <=> other.num * (den_lcm / other.den.value);
	}

	bool arreal::operator==(const arreal& other) const {
		return *this <=> other == 0;
	}

	std::ostream& operator<<(std::ostream& out, const arreal& val) {
		out << val.num;
		if (val.den != 1) {
			out << "/" << val.den;
		}
		return out;
	}

	std::istream& operator>>(std::istream& in, arreal& val) {
		std::string s_value;
		in >> s_value;
		unsigned long long pos = s_value.find('/');
		std::stringstream ss_num(s_value.substr(0, pos));
		arint _num;
		ss_num >> _num;
		arint _den = 1;
		if (pos != std::string::npos) {
			std::stringstream ss_den(s_value.substr(pos + 1));
			ss_den >> _den;
		}
		val = arreal(_num, _den);
		return in;
	}
}