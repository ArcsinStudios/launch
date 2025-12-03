#include "goodmath_arint.h"

namespace launch {
	arint_specval operator|(arint_specval lhs, arint_specval rhs) {
		return static_cast<arint_specval>(
			static_cast<std::underlying_type_t<arint_specval>>(lhs) |
			static_cast<std::underlying_type_t<arint_specval>>(rhs)
		);
	}
	arint_specval operator&(arint_specval lhs, arint_specval rhs) {
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
		return arint(0) - *this;
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
		return (*this <=> other) == 0;
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
		char sign = (in >> std::ws).peek();
		unsigned long long value;
		if (sign == '+' || sign == '-') {
			in.get();
		}
		in >> value;
		if (sign == '-') {
			val = arint(value, arint_specval::neg);
		}
		else {
			val = arint(value);
		}
		return in;
	}
}