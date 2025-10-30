#include "hedgehog_iterators.h"
#include "hedgehog_impl.h"

namespace launch {
	hedgehog_elemproxy& hedgehog_iterator::operator*() const {
		return (*origin)[index];
	}

	hedgehog_iterator& hedgehog_iterator::operator++() {
		++index;
		return *this;
	}

	hedgehog_iterator hedgehog_iterator::operator++(int) {
		hedgehog_iterator temp = *this;
		++*this;
		return temp;
	}

	hedgehog_iterator& hedgehog_iterator::operator--() {
		--index;
		return *this;
	}

	hedgehog_iterator hedgehog_iterator::operator--(int) {
		hedgehog_iterator temp = *this;
		--*this;
		return temp;
	}

	hedgehog_iterator& hedgehog_iterator::operator+=(std::ptrdiff_t n) {
		index += n;
		return *this;
	}

	hedgehog_iterator& hedgehog_iterator::operator-=(std::ptrdiff_t n) {
		index -= n;
		return *this;
	}

	hedgehog_iterator hedgehog_iterator::operator+(std::ptrdiff_t n) const {
		hedgehog_iterator temp = *this;
		temp += n;
		return temp;
	}

	hedgehog_iterator operator+(std::ptrdiff_t n, const hedgehog_iterator& other) {
		hedgehog_iterator temp = other;
		temp += n;
		return temp;
	}

	hedgehog_iterator hedgehog_iterator::operator-(std::ptrdiff_t n) const {
		hedgehog_iterator temp = *this;
		temp -= n;
		return temp;
	}

	std::ptrdiff_t hedgehog_iterator::operator-(const hedgehog_iterator& other) const {
		return (std::ptrdiff_t)index - other.index;
	}

	hedgehog_elemproxy& hedgehog_iterator::operator[](std::ptrdiff_t n) const {
		return *(*this + n);
	}

	std::strong_ordering hedgehog_iterator::operator<=>(const hedgehog_iterator& other) const {
		return index <=> other.index;
	}

	bool hedgehog_iterator::operator==(const hedgehog_iterator& other) const {
		return (*this <=> other) == 0;
	}

	const hedgehog_elemproxy& hedgehog_const_iterator::operator*() const {
		return (*origin)[index];
	}

	hedgehog_const_iterator& hedgehog_const_iterator::operator++() {
		++index;
		return *this;
	}

	hedgehog_const_iterator hedgehog_const_iterator::operator++(int) {
		hedgehog_const_iterator temp = *this;
		++*this;
		return temp;
	}

	hedgehog_const_iterator& hedgehog_const_iterator::operator--() {
		--index;
		return *this;
	}

	hedgehog_const_iterator hedgehog_const_iterator::operator--(int) {
		hedgehog_const_iterator temp = *this;
		--*this;
		return temp;
	}

	hedgehog_const_iterator& hedgehog_const_iterator::operator+=(std::ptrdiff_t n) {
		index += n;
		return *this;
	}

	hedgehog_const_iterator& hedgehog_const_iterator::operator-=(std::ptrdiff_t n) {
		index -= n;
		return *this;
	}

	hedgehog_const_iterator hedgehog_const_iterator::operator+(std::ptrdiff_t n) const {
		hedgehog_const_iterator temp = *this;
		temp += n;
		return temp;
	}

	hedgehog_const_iterator operator+(std::ptrdiff_t n, const hedgehog_const_iterator& other) {
		hedgehog_const_iterator temp = other;
		temp += n;
		return temp;
	}

	hedgehog_const_iterator hedgehog_const_iterator::operator-(std::ptrdiff_t n) const {
		hedgehog_const_iterator temp = *this;
		temp -= n;
		return temp;
	}

	std::ptrdiff_t hedgehog_const_iterator::operator-(const hedgehog_const_iterator& other) const {
		return (std::ptrdiff_t)index - other.index;
	}

	const hedgehog_elemproxy& hedgehog_const_iterator::operator[](std::ptrdiff_t n) const {
		return *(*this + n);
	}

	std::strong_ordering hedgehog_const_iterator::operator<=>(const hedgehog_const_iterator& other) const {
		return index <=> other.index;
	}

	bool hedgehog_const_iterator::operator==(const hedgehog_const_iterator& other) const {
		return (*this <=> other) == 0;
	}
}