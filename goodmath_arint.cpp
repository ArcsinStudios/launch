#include "goodmath_arint.h"

namespace launch {
	long long arint::_Pow(long long x, long long y) const {
		long long p = 1;
		for (long long i = 0; i < y; ++i) {
			p *= x;
		}
		return p;
	}

	arint::operator long long() const {
		return value;
	}

	arint& arint::operator=(const arint& other) {
		value = other.value;
		return *this;
	}

	arint& arint::operator+=(const arint& other) {
		value += other.value;
		return *this;
	}

	arint& arint::operator-=(const arint& other) {
		value -= other.value;
		return *this;
	}

	arint& arint::operator*=(const arint& other) {
		value *= other.value;
		return *this;
	}

	arint& arint::operator/=(const arint& other) {
		value /= other.value;
		return *this;
	}

	arint& arint::operator^=(const arint& other) {
		value = _Pow(value, other.value);
		return *this;
	}

	arint& arint::operator%=(const arint& other) {
		value %= other.value;
		return *this;
	}

	arint& arint::operator++() {
		++value;
		return *this;
	}

	arint arint::operator++(int) {
		return value++;
	}

	arint& arint::operator--() {
		--value;
		return *this;
	}

	arint arint::operator--(int) {
		return value--;
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

	arint arint::operator-() const {
		return -value;
	}

	std::strong_ordering arint::operator<=>(const arint& other) const {
		return value <=> other.value;
	}

	bool arint::operator==(const arint& other) const {
		return (*this <=> other) == 0;
	}

	arint arint::operator[](size_t digit) const {
		return std::abs(value) / _Pow(10, digit) % 10;
	}
}