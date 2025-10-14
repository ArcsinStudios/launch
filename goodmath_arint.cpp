#include "goodmath_arint.h"

namespace launch {
	arint::operator long long() const {
		return value;
	}

	arint& arint::operator=(arint other) {
		value = other.value;
		return *this;
	}

	arint& arint::operator+=(arint other) {
		value += other.value;
		return *this;
	}

	arint& arint::operator-=(arint other) {
		value -= other.value;
		return *this;
	}

	arint& arint::operator*=(arint other) {
		value *= other.value;
		return *this;
	}

	arint& arint::operator/=(arint other) {
		value /= other.value;
		return *this;
	}

	arint& arint::operator^=(arint other) {
		value = std::pow(value, other.value);
		return *this;
	}

	arint& arint::operator%=(arint other) {
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

	arint arint::operator+(arint other) const {
		arint temp = *this;
		temp += other;
		return temp;
	}

	arint arint::operator-(arint other) const {
		arint temp = *this;
		temp -= other;
		return temp;
	}

	arint arint::operator*(arint other) const {
		arint temp = *this;
		temp *= other;
		return temp;
	}

	arint arint::operator/(arint other) const {
		arint temp = *this;
		temp /= other;
		return temp;
	}

	arint arint::operator^(arint other) const {
		arint temp = *this;
		temp ^= other;
		return temp;
	}

	arint arint::operator%(arint other) const {
		arint temp = *this;
		temp %= other;
		return temp;
	}

	arint arint::operator-() const {
		return -value;
	}

	std::strong_ordering arint::operator<=>(arint other) const {
		return value <=> other.value;
	}

	arint arint::operator[](size_t digit) const {
		return std::abs(value) / (long long)std::pow(10, digit) % 10;
	}
}