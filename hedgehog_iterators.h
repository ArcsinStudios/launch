#pragma once

#include <vector>

namespace launch {
	class hedgehog;
	class hedgehog_elemproxy;

	class hedgehog_iterator {
	private:
		hedgehog* origin;
		int index;

	public:
		hedgehog_iterator(hedgehog* _origin, int _index) : origin(_origin), index(_index) {}

		hedgehog_elemproxy& operator*() const;

		hedgehog_iterator& operator++();

		hedgehog_iterator operator++(int);

		hedgehog_iterator& operator--();

		hedgehog_iterator operator--(int);

		hedgehog_iterator& operator+=(std::ptrdiff_t n);

		hedgehog_iterator& operator-=(std::ptrdiff_t n);

		hedgehog_iterator operator+(std::ptrdiff_t n) const;

		friend hedgehog_iterator operator+(std::ptrdiff_t n, const hedgehog_iterator& other);

		hedgehog_iterator operator-(std::ptrdiff_t n) const;

		std::ptrdiff_t operator-(const hedgehog_iterator& other) const;

		hedgehog_elemproxy& operator[](std::ptrdiff_t n) const;

		bool operator==(const hedgehog_iterator& other) const;

		bool operator!=(const hedgehog_iterator& other) const;

		bool operator<(const hedgehog_iterator& other) const;

		bool operator>(const hedgehog_iterator& other) const;

		bool operator<=(const hedgehog_iterator& other) const;

		bool operator>=(const hedgehog_iterator& other) const;
	};

	class hedgehog_const_iterator {
	private:
		const hedgehog* origin;
		int index;

	public:
		hedgehog_const_iterator(const hedgehog* _origin, int _index) : origin(_origin), index(_index) {}

		const hedgehog_elemproxy& operator*() const;

		hedgehog_const_iterator& operator++();

		hedgehog_const_iterator operator++(int);

		hedgehog_const_iterator& operator--();

		hedgehog_const_iterator operator--(int);

		hedgehog_const_iterator& operator+=(std::ptrdiff_t n);

		hedgehog_const_iterator& operator-=(std::ptrdiff_t n);

		hedgehog_const_iterator operator+(std::ptrdiff_t n) const;

		friend hedgehog_const_iterator operator+(std::ptrdiff_t n, const hedgehog_const_iterator& other);

		hedgehog_const_iterator operator-(std::ptrdiff_t n) const;

		std::ptrdiff_t operator-(const hedgehog_const_iterator& other) const;

		const hedgehog_elemproxy& operator[](std::ptrdiff_t n) const;

		bool operator==(const hedgehog_const_iterator& other) const;

		bool operator!=(const hedgehog_const_iterator& other) const;

		bool operator<(const hedgehog_const_iterator& other) const;

		bool operator>(const hedgehog_const_iterator& other) const;

		bool operator<=(const hedgehog_const_iterator& other) const;

		bool operator>=(const hedgehog_const_iterator& other) const;
	};
}