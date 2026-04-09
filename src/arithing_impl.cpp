#include "../include/launch_config.h"

#include "../include/arithing_impl.h"

namespace leisure {
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
			nan = nan || other.nan || inf && other.inf && sign != other.sign;
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
			nan = nan || other.nan || inf && !other.value || !value && other.inf;
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
			nan = nan || other.nan || inf && other.inf || !value && !other.value;
			inf = !nan && (inf || value && !other.value);
			value = (!nan && !inf && other.inf) ? 0 : value;
			return *this;
		}
		value /= other.value;
		return *this;
	}

	arint& arint::operator^=(const arint& other) {
		if (!value || nan || other.nan || inf || other.inf) {
			nan = nan || other.nan || inf && !other.value || !value && !other.value || !sign && other.inf;
			inf = !nan || other.inf && value;
			return *this;
		}
		if (value == 1) {
			sign = sign || !(other.value % 2);
			return *this;
		}
		if (!other.sign) {
			value = 0;
			return *this;
		}
		if (other > 64) {
			inf = true;
			return *this;
		}
		arint p = 1;
		for (arint i = 0; i < other; ++i) {
			if (p.inf) {
				*this = p;
				return *this;
			}
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

	arint arint::operator++(int){
		arint temp = *this;
		++*this;
		return temp;
	}

	arint& arint::operator--() {
		*this -= 1;
		return *this;
	}

	arint arint::operator--(int){
		arint temp = *this;
		--*this;
		return temp;
	}

	arint operator+(const arint& a, const arint& b) {
		arint temp = a;
		temp += b;
		return temp;
	}

	arint operator-(const arint& a, const arint& b) {
		arint temp = a;
		temp -= b;
		return temp;
	}

	arint operator*(const arint& a, const arint& b) {
		arint temp = a;
		temp *= b;
		return temp;
	}

	arint operator/(const arint& a, const arint& b) {
		arint temp = a;
		temp /= b;
		return temp;
	}

	arint operator^(const arint& a, const arint& b) {
		arint temp = a;
		temp ^= b;
		return temp;
	}

	arint operator%(const arint& a, const arint& b) {
		arint temp = a;
		temp %= b;
		return temp;
	}

	arint arint::operator+() const {
		return *this;
	}

	arint arint::operator-() const {
		arint temp = *this;
		temp.sign = !temp.sign;
		return temp;
	}

	std::partial_ordering operator<=>(const arint& a, const arint& b) {
		if (a.nan || b.nan) {
			return std::partial_ordering::unordered;
		}
		int a_lvl = (a.sign ? 1 : -1) * (a.inf ? 2 : 1);
		int b_lvl = (b.sign ? 1 : -1) * (b.inf ? 2 : 1);
		if (a_lvl != b_lvl) {
			return a_lvl <=> b_lvl;
		}
		if (a_lvl == 2 || a_lvl == -2) {
			return std::strong_ordering::equal;
		}
		return (a_lvl > 0) ? (a.value <=> b.value) : (b.value <=> a.value);
	}

	bool operator==(const arint& a, const arint& b) {
		return a <=> b == 0;
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

	unsigned long long abs(const arint& val) {
		return val.value;
	}

	unsigned long long sign(const arint& val) {
		return val.sign;
	}

	unsigned long long nan(const arint& val) {
		return val.nan;
	}

	unsigned long long inf(const arint& val) {
		return val.inf;
	}

	constexpr void arreal::adjust() {
		if (num.sign && !den.sign) {
			num.sign = false;
			den.sign = true;
		}
		if (num.sign == den.sign) {
			num.sign = true;
			den.sign = true;
		}
		if (num.nan || den.nan || num.inf || den.inf) {
			return;
		}
		if (den.value == 0) {
			num.inf = true;
			den.value = 1;
			return;
		}
		unsigned long long nd_gcd = std::gcd(num.value, den.value);
		num.value /= nd_gcd;
		den.value /= nd_gcd;
	}

	constexpr arreal::arreal(const arint& _num, const arint& _den) : num(_num), den(_den) {
		adjust();
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
		adjust();
		return *this;
	}

	arreal& arreal::operator-=(const arreal& other) {
		*this += -other;
		return *this;
	}

	arreal& arreal::operator*=(const arreal& other) {
		num *= other.num;
		den *= other.den;
		adjust();
		return *this;
	}

	arreal& arreal::operator/=(const arreal& other) {
		arreal temp(other.den, other.num);
		*this *= temp;
		return *this;
	}

	arreal& arreal::operator%=(const arreal& other) {
		if (den == other.den) {
			num %= other.num;
		}
		else {
			unsigned long long den_lcm = std::lcm(den.value, other.den.value);
			num = num * (den_lcm / den.value) % other.num * (den_lcm / other.den.value);
			den.value = den_lcm;
		}
		adjust();
		return *this;
	}

	arreal operator+(const arreal& a, const arreal& b) {
		arreal temp = a;
		temp += b;
		return temp;
	}

	arreal operator-(const arreal& a, const arreal& b) {
		arreal temp = a;
		temp -= b;
		return temp;
	}

	arreal operator*(const arreal& a, const arreal& b) {
		arreal temp = a;
		temp *= b;
		return temp;
	}

	arreal operator/(const arreal& a, const arreal& b) {
		arreal temp = a;
		temp /= b;
		return temp;
	}

	arreal operator%(const arreal& a, const arreal& b) {
		arreal temp = a;
		temp %= b;
		return temp;
	}

	arreal arreal::operator+() const {
		return *this;
	}

	arreal arreal::operator-() const {
		return arreal(-num, den);
	}

	std::partial_ordering operator<=>(const arreal& a, const arreal& b) {
		unsigned long long
			a_den_value = abs(a.den),
			b_den_value = abs(b.den),
			den_lcm = std::lcm(a_den_value, b_den_value);
		return a.num * (den_lcm / a_den_value) <=> b.num * (den_lcm / b_den_value);
	}

	bool operator==(const arreal& a, const arreal& b) {
		return a <=> b == 0;
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
		arint temp_num;
		ss_num >> temp_num;
		arint temp_den = 1;
		if (pos != std::string::npos) {
			std::stringstream ss_den(s_value.substr(pos + 1));
			ss_den >> temp_den;
		}
		val = arreal(temp_num, temp_den);
		return in;
	}

	arint numerator(const arreal& val) {
		return val.num;
	}

	arint denominator(const arreal& val) {
		return val.den;
	}

	std::string to_decimal(const arreal& val) {
		if (nan(val.num)) {
			return "NaN";
		}
		bool val_num_inf = inf(val.num);
		if (inf(val.den)) {
			return val_num_inf ? "NaN" : "0";
		}
		unsigned long long
			val_num_value = abs(val.num),
			val_den_value = abs(val.den);
		bool val_num_sign = sign(val.num);
		std::string res;
		if (!val_num_sign) {
			res += "-";
		}
		if (inf(val.num)) {
			res += "inf";
			return res;
		}
		std::string res_str = std::to_string(val_num_value / val_den_value);
		res += res_str;
		unsigned long long rem = val_num_value % val_den_value;
		if (!rem) {
			return res;
		}
		res += ".";
		size_t res_length = res.length();
		unsigned long long num2 = rem * 10;
		std::vector<unsigned long long> rem_before = { rem };
		while (rem) {
			if (++res_length > 100) {
				throw std::runtime_error("to_decimal: result too long");
			}
			res += std::to_string(num2 / val_den_value);
			rem = num2 % val_den_value;
			num2 = rem * 10;
			std::vector<unsigned long long>::const_iterator it = std::find(rem_before.begin(), rem_before.end(), rem);
			if (it != rem_before.end()) {
				size_t pos = !val_num_sign + res_str.length() + 1 + (it - rem_before.begin());
				res = res.substr(0, pos) + "(" + res.substr(pos) + ")";
				break;
			}
			rem_before.push_back(rem);
		}
		return res;
	}
}