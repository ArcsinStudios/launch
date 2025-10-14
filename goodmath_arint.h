#pragma once

#include <cmath>
#include <compare>

namespace launch {
	class arint {
	private:
		long long value;

	public:
		arint() = default;

		arint(long long _value) : value(_value) {}

		explicit operator long long() const;

		arint& operator=(arint other);

		arint& operator+=(arint other);

		arint& operator-=(arint other);

		arint& operator*=(arint other);

		arint& operator/=(arint other);

		arint& operator^=(arint other);

		arint& operator%=(arint other);

		arint& operator++();

		arint operator++(int);

		arint& operator--();

		arint operator--(int);

		arint operator+(arint other) const;

		arint operator-(arint other) const;

		arint operator*(arint other) const;

		arint operator/(arint other) const;

		arint operator^(arint other) const;

		arint operator%(arint other) const;

		arint operator-() const;

		std::strong_ordering operator<=>(arint other) const;

		arint operator[](size_t digit) const;
	};
}