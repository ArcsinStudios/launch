export module arithing:impl;

import std;

namespace leisure {
	export enum class arint_specval : unsigned char {
		nop = 0b0000,
		neg = 0b0001,
		nan = 0b0010,
		inf = 0b0100
	};

	export constexpr arint_specval operator|(arint_specval lhs, arint_specval rhs);
	export constexpr arint_specval operator&(arint_specval lhs, arint_specval rhs);

	export class arreal;

	export class arint {
	private:
		unsigned long long value;
		bool sign;
		bool nan;
		bool inf;

	public:
		friend class arreal;

		constexpr arint(unsigned long long _value = 0, arint_specval specval = arint_specval::nop) :
			value(_value),
			sign(!static_cast<bool>(specval& arint_specval::neg)),
			nan(static_cast<bool>(specval& arint_specval::nan)),
			inf(static_cast<bool>(specval& arint_specval::inf))
		{
		}

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

		friend unsigned long long abs(const arint& val);

		friend unsigned long long sign(const arint& val);

		friend unsigned long long nan(const arint& val);

		friend unsigned long long inf(const arint& val);
	};

	export arint operator+(const arint& a, const arint& b);

	export arint operator-(const arint& a, const arint& b);

	export arint operator*(const arint& a, const arint& b);

	export arint operator/(const arint& a, const arint& b);

	export arint operator^(const arint& a, const arint& b);

	export arint operator%(const arint& a, const arint& b);

	export class arreal {
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

		friend arint numerator(const arreal& val);

		friend arint denominator(const arreal& val);

		friend std::string to_decimal(const arreal& val);
	};

	export arreal operator+(const arreal& a, const arreal& b);

	export arreal operator-(const arreal& a, const arreal& b);

	export arreal operator*(const arreal& a, const arreal& b);

	export arreal operator/(const arreal& a, const arreal& b);

	export arreal operator%(const arreal& a, const arreal& b);
}