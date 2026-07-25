module genev:impl;

import std;

namespace leisure {
	size_t genev::unit_to_index(std::string unit_str) {
		if (!unit_str.length() || unit_str.length() > 3) {
			throw std::runtime_error("genev::unit_to_index: unit not found");
		}
		for (size_t i = 0; i < genev::dim_count; ++i) {
			if (units_str[i] == unit_str) {
				return i;
			}
		}
		throw std::runtime_error("genev::unit_to_index: unit not found");
	}

	size_t genev::prefix_to_index(std::string prefix_str) {
		if (!prefix_str.length() || prefix_str.length() > 3) {
			throw std::runtime_error("genev::prefix_to_index: unit not found");
		}
		for (size_t i = 0; i < genev::prefix_count; ++i) {
			if (prefixes_str[i] == prefix_str) {
				return i;
			}
		}
		throw std::runtime_error("genev::prefix_to_index: unit not found");
	}

	double genev::value() const {
		return value_;
	}

	std::array<long long, genev::dim_count> genev::unit() const {
		return unit_;
	}

	genev& genev::operator+=(const genev& other) {
		if (unit_ != other.unit_) {
			throw std::runtime_error("genev::operator+=: unit mismatch");
		}
		value_ += other.value_;
		return *this;
	}

	genev& genev::operator-=(const genev& other) {
		*this += -other;
		return *this;
	}

	genev& genev::operator*=(const genev& other) {
		value_ *= other.value_;
		for (size_t i = 0; i < dim_count; ++i) {
			unit_[i] += other.unit_[i];
		}
		return *this;
	}

	genev& genev::operator/=(const genev& other) {
		value_ /= other.value_;
		for (size_t i = 0; i < dim_count; ++i) {
			unit_[i] -= other.unit_[i];
		}
		return *this;
	}

	genev operator+(const genev& a, const genev& b) {
		genev temp = a;
		temp += b;
		return temp;
	}

	genev operator-(const genev& a, const genev& b) {
		genev temp = a;
		temp -= b;
		return temp;
	}

	genev operator*(const genev& a, const genev& b) {
		genev temp = a;
		temp *= b;
		return temp;
	}

	genev operator/(const genev& a, const genev& b) {
		genev temp = a;
		temp /= b;
		return temp;
	}

	genev operator^(const genev& a, long long b) {
		double new_value = pow(a.value(), b);
		std::array<long long, genev::dim_count> new_unit = a.unit();
		for (long long& dim : new_unit) {
			dim *= b;
		}
		return genev(new_value, new_unit);
	}

	genev genev::operator+() const {
		return *this;
	}

	genev genev::operator-() const {
		genev temp = *this;
		temp.value_ = -value_;
		return temp;
	}

	std::partial_ordering genev::operator<=>(const genev& other) const {
		if (unit_ != other.unit_) {
			return std::partial_ordering::unordered;
		}
		return value_ <=> other.value_;
	}

	bool genev::operator==(const genev& other) const {
		return *this <=> other == 0;
	}

	std::ostream& operator<<(std::ostream& out, const genev& val) {
		double converted = val.value_ * std::pow(1000, -val.unit_[1]);
		out << converted;
		bool dimensionless = true;
		for (const long long& dim : val.unit_) {
			if (dim) {
				dimensionless = false;
				break;
			}
		}
		if (dimensionless) {
			return out;
		}
		out << " ";
		size_t printed = 0;
		for (size_t i = 0; i < genev::dim_count; ++i) {
			if (!val.unit_[i]) {
				continue;
			}
			if (printed++) {
				out << (val.unit_[i] > 0 ? "*" : "/");
				out << units_str_si[i];
				long long abs_exp = std::abs(val.unit_[i]);
				if (abs_exp != 1) {
					out << "^" << std::abs(val.unit_[i]);
				}
			}
			else {
				out << units_str_si[i];
				if (val.unit_[i] != 1) {
					out << "^" << val.unit_[i];
				}
			}
		}
		return out;
	}

	std::istream& operator>>(std::istream& in, genev& val) {
		std::string value;
		in >> value;
		if (value.starts_with("#")) {
			val = std::stod(value.substr(1));
			return in;
		}
		val = std::stod(value);
		std::string unit;
		in >> unit;
		std::vector<std::string> split_units;
		size_t start = 0;
		size_t end = unit.find_first_of("*/");
		while (end != std::string::npos) {
			split_units.push_back(unit.substr(start, end - start));
			start = end;
			end = unit.find_first_of("*/", start + 1);
		}
		split_units.push_back(unit.substr(start));
		for (const std::string& split_unit : split_units) {
			std::function<genev(const genev&)> prefix = [](const genev& val) { return val; };
			genev base_unit;
			long long exp = 1;
			size_t pow_pos = split_unit.find('^');
			char first_char = split_unit[0];
			std::string base_unit_str;
			if (first_char == '*' || first_char == '/') {
				base_unit_str = split_unit.substr(1, pow_pos - 1);
			}
			else {
				base_unit_str = split_unit.substr(0, pow_pos);
			}
			try {
				base_unit = units[genev::unit_to_index(base_unit_str)];
			}
			catch (const std::runtime_error&) {
				bool success = false;
				for (const std::string& prefix_str : prefixes_str_sorted) {
					if (base_unit_str.starts_with(prefix_str)) {
						prefix = prefixes[genev::prefix_to_index(prefix_str)];
						base_unit_str = base_unit_str.substr(prefix_str.length());
						success = true;
						break;
					}
				}
				if (!success) {
					throw std::runtime_error("operator>>(std::istream&, genev&): unsupported unit: " + base_unit_str);
				}
			}
			base_unit = units[genev::unit_to_index(base_unit_str)];
			if (pow_pos != std::string::npos) {
				exp = std::stoll(split_unit.substr(pow_pos + 1));
			}
			if (first_char == '/') {
				exp = -exp;
			}
			val *= prefix(base_unit) ^ exp;
		}
		return in;
	}

	const genev     meter(1, { 1, 0, 0, 0, 0, 0, 0, 0, 0 });
	const genev      gram(1, { 0, 1, 0, 0, 0, 0, 0, 0, 0 });
	const genev    second(1, { 0, 0, 1, 0, 0, 0, 0, 0, 0 });
	const genev    ampere(1, { 0, 0, 0, 1, 0, 0, 0, 0, 0 });
	const genev    kelvin(1, { 0, 0, 0, 0, 1, 0, 0, 0, 0 });
	const genev   candela(1, { 0, 0, 0, 0, 0, 1, 0, 0, 0 });
	const genev      mole(1, { 0, 0, 0, 0, 0, 0, 1, 0, 0 });
	const genev    radian(1, { 0, 0, 0, 0, 0, 0, 0, 1, 0 });
	const genev steradian(1, { 0, 0, 0, 0, 0, 0, 0, 0, 1 });

	genev peta(const genev& unit) {
		return 1e15 * unit;
	}

	genev tera(const genev& unit) {
		return 1e12 * unit;
	}

	genev giga(const genev& unit) {
		return 1e9 * unit;
	}

	genev mega(const genev& unit) {
		return 1e6 * unit;
	}

	genev kilo(const genev& unit) {
		return 1e3 * unit;
	}

	genev hecto(const genev& unit) {
		return 1e2 * unit;
	}

	genev deca(const genev& unit) {
		return 1e1 * unit;
	}

	genev deci(const genev& unit) {
		return 1e-1 * unit;
	}

	genev centi(const genev& unit) {
		return 1e-2 * unit;
	}

	genev milli(const genev& unit) {
		return 1e-3 * unit;
	}

	genev micro(const genev& unit) {
		return 1e-6 * unit;
	}

	genev nano(const genev& unit) {
		return 1e-9 * unit;
	}

	genev pico(const genev& unit) {
		return 1e-12 * unit;
	}

	genev femto(const genev& unit) {
		return 1e-15 * unit;
	}

	const genev hertz = second ^ -1;
	const genev newton = kilo(gram) * meter / (second ^ 2);
	const genev pascal = newton / (meter ^ 2);
	const genev joule = newton * meter;
	const genev watt = joule / second;
	const genev coulomb = ampere * second;
	const genev volt = watt / ampere;
	const genev farad = coulomb / volt;
	const genev ohm = volt / ampere;
	const genev siemens = ampere / volt;
	const genev weber = volt * second;
	const genev tesla = weber / (meter ^ 2);
	const genev henry = weber / ampere;
	const genev lumen = candela * steradian;
	const genev lux = lumen / (meter ^ 2);

	const genev minute = 60 * second;
	const genev hour = 60 * minute;
	const genev day = 24 * hour;
	const genev degree = std::numbers::pi / 180 * radian;
	const genev arcminute = 1.0 / 60 * degree;
	const genev arcsecond = 1.0 / 60 * arcminute;
	const genev hectare = 10000 * (meter ^ 2);
	const genev liter = 0.001 * (meter ^ 3);
	const genev ton = 1000 * kilo(gram);

	const std::array<genev, genev::dim_count> units =
		{ meter, gram, second, ampere, kelvin, candela, mole, radian, steradian };

	const std::array<std::string, genev::dim_count> units_str =
		{ "m", "g", "s", "A", "K", "cd", "mol", "rad", "sr" };

	const std::array<std::string, genev::dim_count> units_str_si =
		{ "m", "kg", "s", "A", "K", "cd", "mol", "rad", "sr" };

	const std::array<std::function<genev(const genev&)>, genev::prefix_count> prefixes =
		{ peta, tera, giga, mega, kilo, hecto, deca, deci, centi, milli, micro, nano, pico, femto };

	const std::array<std::string, genev::prefix_count> prefixes_str =
		{ "P", "T", "G", "M", "k", "h", "da", "d", "c", "m", "u", "n", "p", "f" };

	const std::array<std::string, genev::prefix_count> prefixes_str_sorted =
		{ "da", "P", "T", "G", "M", "k", "h", "d", "c", "m", "u", "n", "p", "f" };
}