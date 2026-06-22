#pragma once

#include <array>
#include <cmath>
#include <compare>
#include <functional>
#include <iostream>
#include <numbers>
#include <stdexcept>
#include <string>
#include <vector>

namespace leisure {
	class genev {
	public:
		static const size_t dim_count = 9;
		static const size_t prefix_count = 14;

	private:
		double value_;
		std::array<long long, dim_count> unit_;

		static size_t unit_to_index(std::string unit_str);
		static size_t prefix_to_index(std::string prefix_str);

	public:
		genev(double value = 0, std::array<long long, dim_count> unit = {}) : value_(value), unit_(unit) {}

		double value() const;

		std::array<long long, dim_count> unit() const;

		genev& operator+=(const genev& other);

		genev& operator-=(const genev& other);

		genev& operator*=(const genev& other);

		genev& operator/=(const genev& other);

		genev operator+() const;

		genev operator-() const;

		std::partial_ordering operator<=>(const genev& other) const;

		bool operator==(const genev& other) const;

		friend std::ostream& operator<<(std::ostream& out, const genev& val);

		friend std::istream& operator>>(std::istream& in, genev& val);
	};
	
	genev operator+(const genev& a, const genev& b);

	genev operator-(const genev& a, const genev& b);

	genev operator*(const genev& a, const genev& b);

	genev operator/(const genev& a, const genev& b);

	genev operator^(const genev& a, long long b);

	extern const genev meter;
	extern const genev gram;
	extern const genev second;
	extern const genev ampere;
	extern const genev kelvin;
	extern const genev candela;
	extern const genev mole;
	extern const genev radian;
	extern const genev steradian;

	genev peta(const genev& unit);
	genev tera(const genev& unit);
	genev giga(const genev& unit);
	genev mega(const genev& unit);
	genev kilo(const genev& unit);
	genev hecto(const genev& unit);
	genev deca(const genev& unit);
	genev deci(const genev& unit);
	genev centi(const genev& unit);
	genev milli(const genev& unit);
	genev micro(const genev& unit);
	genev nano(const genev& unit);
	genev pico(const genev& unit);
	genev femto(const genev& unit);

	extern const genev hertz;
	extern const genev newton;
	extern const genev pascal;
	extern const genev joule;
	extern const genev watt;
	extern const genev coulomb;
	extern const genev volt;
	extern const genev farad;
	extern const genev ohm;
	extern const genev siemens;
	extern const genev weber;
	extern const genev tesla;
	extern const genev henry;
	extern const genev lumen;
	extern const genev lux;

	extern const genev minute;
	extern const genev hour;
	extern const genev day;
	extern const genev degree;
	extern const genev arcminute;
	extern const genev arcsecond;
	extern const genev hectare;
	extern const genev liter;
	extern const genev ton;

	extern const std::array<genev, genev::dim_count> units;
	extern const std::array<std::string, genev::dim_count> units_str;
	extern const std::array<std::string, genev::dim_count> units_str_si;
	extern const std::array<std::function<genev(const genev&)>, genev::prefix_count> prefixes;
	extern const std::array<std::string, genev::prefix_count> prefixes_str;
	extern const std::array<std::string, genev::prefix_count> prefixes_str_sorted;
}