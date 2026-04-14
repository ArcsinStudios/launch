#pragma once

#include <algorithm>
#include <compare>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace leisure {
	enum class base_unit : unsigned char {
		m,
		g,
		s,
		A,
		K,
		cd,
		mol
	};

	enum class unit_prefix : unsigned char {
		G,
		M,
		k,
		h,
		da,
		none,
		d,
		c,
		m,
		u,
		n
	};

	extern std::unordered_map<base_unit, std::string> unit_str_map;
	extern std::unordered_map<unit_prefix, std::string> prefix_str_map;
	extern std::unordered_map<unit_prefix, signed char> prefix_exp_map;

	extern std::unordered_map<std::string, base_unit> str_unit_map;
	extern std::unordered_map<std::string, unit_prefix> str_prefix_map;
	extern std::unordered_map<signed char, unit_prefix> exp_prefix_map;

	using unit_type = std::tuple<unit_prefix, base_unit, long long>;

	class genev {
	private:
		double value;
		std::vector<unit_type> unit;

		bool same_unit(const genev& other) const;

	public:
		genev() = default;

		explicit genev(std::string str);

		genev& operator+=(const genev& other);

		genev& operator-=(const genev& other);

		genev& operator*=(const genev& other);

		genev& operator/=(const genev& other);

		genev operator+(const genev& other) const;

		genev operator-(const genev& other) const;

		genev operator*(const genev& other) const;

		genev operator/(const genev& other) const;

		genev operator+() const;

		genev operator-() const;

		std::partial_ordering operator<=>(const genev& other) const;

		bool operator==(const genev& other) const;

		friend std::ostream& operator<<(std::ostream& out, const genev& val);

		friend std::istream& operator>>(std::istream& in, genev& val);

		friend genev unify(const genev& orig);

		friend genev simplify(const genev& orig);

		friend genev convert(const genev& orig, const std::string& new_unit);
	};
}