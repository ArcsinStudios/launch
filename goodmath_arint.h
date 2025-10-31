#pragma once

#include <cmath>
#include <compare>

namespace launch {
	class arint {
	private:
		long long value;

		long long _Pow(long long x, long long y) const;

	public:
		arint() = default;

		arint(long long _value) : value(_value) {}

		explicit operator long long() const;

		arint& operator=(const arint& other);

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

		arint operator-() const;

		std::strong_ordering operator<=>(const arint& other) const;

		bool operator==(const arint& other) const;

		arint operator[](size_t digit) const;
	};
}