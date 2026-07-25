export module genev:impl;

import std;

namespace leisure {
	export class genev {
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
	
	export genev operator+(const genev& a, const genev& b);

	export genev operator-(const genev& a, const genev& b);

	export genev operator*(const genev& a, const genev& b);

	export genev operator/(const genev& a, const genev& b);

	export genev operator^(const genev& a, long long b);

	export extern const genev meter;
	export extern const genev gram;
	export extern const genev second;
	export extern const genev ampere;
	export extern const genev kelvin;
	export extern const genev candela;
	export extern const genev mole;
	export extern const genev radian;
	export extern const genev steradian;

	export genev peta(const genev& unit);
	export genev tera(const genev& unit);
	export genev giga(const genev& unit);
	export genev mega(const genev& unit);
	export genev kilo(const genev& unit);
	export genev hecto(const genev& unit);
	export genev deca(const genev& unit);
	export genev deci(const genev& unit);
	export genev centi(const genev& unit);
	export genev milli(const genev& unit);
	export genev micro(const genev& unit);
	export genev nano(const genev& unit);
	export genev pico(const genev& unit);
	export genev femto(const genev& unit);

	export extern const genev hertz;
	export extern const genev newton;
	export extern const genev pascal;
	export extern const genev joule;
	export extern const genev watt;
	export extern const genev coulomb;
	export extern const genev volt;
	export extern const genev farad;
	export extern const genev ohm;
	export extern const genev siemens;
	export extern const genev weber;
	export extern const genev tesla;
	export extern const genev henry;
	export extern const genev lumen;
	export extern const genev lux;

	export extern const genev minute;
	export extern const genev hour;
	export extern const genev day;
	export extern const genev degree;
	export extern const genev arcminute;
	export extern const genev arcsecond;
	export extern const genev hectare;
	export extern const genev liter;
	export extern const genev ton;

	export extern const std::array<genev, genev::dim_count> units;
	export extern const std::array<std::string, genev::dim_count> units_str;
	export extern const std::array<std::string, genev::dim_count> units_str_si;
	export extern const std::array<std::function<genev(const genev&)>, genev::prefix_count> prefixes;
	export extern const std::array<std::string, genev::prefix_count> prefixes_str;
	export extern const std::array<std::string, genev::prefix_count> prefixes_str_sorted;
}