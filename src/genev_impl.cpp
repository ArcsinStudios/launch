#include "../include/genev_impl.h"

namespace leisure {
	std::unordered_map<base_unit, std::string> unit_str_map = {
		{ base_unit::m, "m" },
		{ base_unit::g, "g" },
		{ base_unit::s, "s" },
		{ base_unit::A, "A" },
		{ base_unit::K, "K" },
		{ base_unit::cd, "cd" },
		{ base_unit::mol, "mol" }
	};
	std::unordered_map<unit_prefix, std::string> prefix_str_map = {
		{ unit_prefix::G, "G" },
		{ unit_prefix::M, "M" },
		{ unit_prefix::k, "k" },
		{ unit_prefix::h, "h" },
		{ unit_prefix::da, "da" },
		{ unit_prefix::none, "" },
		{ unit_prefix::d, "d" },
		{ unit_prefix::c, "c" },
		{ unit_prefix::m, "m" },
		{ unit_prefix::u, "u" },
		{ unit_prefix::n, "n" }
	};
	std::unordered_map<unit_prefix, signed char> prefix_exp_map = {
		{ unit_prefix::G, 9 },
		{ unit_prefix::M, 6 },
		{ unit_prefix::k, 3 },
		{ unit_prefix::h, 2 },
		{ unit_prefix::da, 1 },
		{ unit_prefix::none, 0 },
		{ unit_prefix::d, -1 },
		{ unit_prefix::c, -2 },
		{ unit_prefix::m, -3 },
		{ unit_prefix::u, -6 },
		{ unit_prefix::n, -9 }
	};

	std::unordered_map<std::string, base_unit> str_unit_map = {
		{ "m", base_unit::m },
		{ "g", base_unit::g },
		{ "s", base_unit::s },
		{ "A", base_unit::A },
		{ "K", base_unit::K },
		{ "cd", base_unit::cd },
		{ "mol", base_unit::mol }
	};
	std::unordered_map<std::string, unit_prefix> str_prefix_map = {
		{ "G", unit_prefix::G },
		{ "M", unit_prefix::M },
		{ "k", unit_prefix::k },
		{ "h", unit_prefix::h },
		{ "da", unit_prefix::da },
		{ "", unit_prefix::none },
		{ "d", unit_prefix::d },
		{ "c", unit_prefix::c },
		{ "m", unit_prefix::m },
		{ "u", unit_prefix::u },
		{ "n", unit_prefix::n }
	};
	std::unordered_map<signed char, unit_prefix> exp_prefix_map = {
		{ 9, unit_prefix::G },
		{ 6, unit_prefix::M },
		{ 3, unit_prefix::k },
		{ 2, unit_prefix::h },
		{ 1, unit_prefix::da },
		{ 0, unit_prefix::none },
		{ -1, unit_prefix::d },
		{ -2, unit_prefix::c },
		{ -3, unit_prefix::m },
		{ -6, unit_prefix::u },
		{ -9, unit_prefix::n }
	};

	bool genev::same_unit(const genev& other) const {
		genev other_copy = simplify(other), this_copy = simplify(*this);
		if (other_copy.unit.size() != this_copy.unit.size()) {
			return false;
		}
		std::sort(
			other_copy.unit.begin(), other_copy.unit.end(),
			[](const unit_type& a, const unit_type& b) {
				return
					static_cast<std::underlying_type_t<base_unit>>(std::get<1>(a)) <
					static_cast<std::underlying_type_t<base_unit>>(std::get<1>(b));
			}
		);
		std::sort(
			this_copy.unit.begin(), this_copy.unit.end(),
			[](const unit_type& a, const unit_type& b) {
				return
					static_cast<std::underlying_type_t<base_unit>>(std::get<1>(a)) <
					static_cast<std::underlying_type_t<base_unit>>(std::get<1>(b));
			}
		);
		return other_copy.unit == this_copy.unit;
	}

	genev::genev(std::string str) {
		size_t ws_pos = str.find(' ');
		value = std::stod(str.substr(0, ws_pos));
		if (ws_pos == std::string::npos) {
			return;
		}
		std::string unit_str = str.substr(ws_pos + 1);
		std::vector<std::string> split_units;
		size_t start = 0;
		size_t end = unit_str.find_first_of("*/");
		while (end != std::string::npos) {
			split_units.push_back(unit_str.substr(start, end - start));
			start = end;
			end = unit_str.find_first_of("*/", start + 1);
		}
		split_units.push_back(unit_str.substr(start));
		std::vector<std::pair<std::string, unit_prefix>> sorted_prefixes(str_prefix_map.begin(), str_prefix_map.end());
		std::sort(
			sorted_prefixes.begin(), sorted_prefixes.end(),
			[](const std::pair<std::string, unit_prefix>& a, const std::pair<std::string, unit_prefix>& b) {
				return a.first.length() > b.first.length();
			}
		);
		for (const std::string& split_unit : split_units) {
			unit_prefix prefix_part = unit_prefix::none;
			base_unit unit_part;
			long long exp_part = 1;
			size_t pow_pos = split_unit.find('^');
			char first_char = split_unit[0];
			std::string unit_part_str;
			if (first_char == '*' || first_char == '/') {
				unit_part_str = split_unit.substr(1, pow_pos - 1);
			}
			else {
				unit_part_str = split_unit.substr(0, pow_pos);
			}
			std::unordered_map<std::string, base_unit>::const_iterator unit_it = str_unit_map.find(unit_part_str);
			if (unit_it == str_unit_map.end()) {
				for (const auto& [prefix_str, prefix] : sorted_prefixes) {
					if (unit_part_str.starts_with(prefix_str)) {
						prefix_part = prefix;
						unit_part_str = unit_part_str.substr(prefix_str.length());
						unit_it = str_unit_map.find(unit_part_str);
						break;
					}
				}
				if (unit_it == str_unit_map.end()) {
					throw std::runtime_error("genev::genev: unsupported base unit: " + unit_part_str);
				}
			}
			unit_part = unit_it->second;
			if (pow_pos != std::string::npos) {
				exp_part = std::stoll(split_unit.substr(pow_pos + 1));
			}
			if (first_char == '/') {
				exp_part = -exp_part;
			}
			unit.push_back({ prefix_part, unit_part, exp_part });
		}
	}

	genev& genev::operator+=(const genev& other) {
		if (!same_unit(other)) {
			throw std::runtime_error("genev::operator+=: type mismatch");
		}
		value += other.value;
		return *this;
	}

	genev& genev::operator-=(const genev& other) {
		*this += -other;
		return *this;
	}

	genev& genev::operator*=(const genev& other) {
		value *= other.value;
		unit.insert(unit.end(), other.unit.begin(), other.unit.end());
		*this = simplify(*this);
		return *this;
	}

	genev& genev::operator/=(const genev& other) {
		value /= other.value;
		for (const auto& [prefix, other_unit, exp] : other.unit) {
			unit.push_back({ prefix, other_unit, -exp });
		}
		*this = simplify(*this);
		return *this;
	}

	genev genev::operator+(const genev& other) const {
		genev temp = *this;
		temp += other;
		return temp;
	}

	genev genev::operator-(const genev& other) const {
		genev temp = *this;
		temp -= other;
		return temp;
	}

	genev genev::operator*(const genev& other) const {
		genev temp = *this;
		temp *= other;
		return temp;
	}

	genev genev::operator/(const genev& other) const {
		genev temp = *this;
		temp /= other;
		return temp;
	}

	genev genev::operator+() const {
		return *this;
	}

	genev genev::operator-() const {
		genev temp = *this;
		temp.value = -value;
		return temp;
	}

	std::partial_ordering genev::operator<=>(const genev& other) const {
		if (!same_unit(other)) {
			return std::partial_ordering::unordered;
		}
		return value <=> other.value;
	}

	bool genev::operator==(const genev& other) const {
		return *this <=> other == 0;
	}

	std::ostream& operator<<(std::ostream& out, const genev& val) {
		out << val.value << " ";
		size_t unit_size = val.unit.size();
		for (size_t i = 0; i < unit_size; ++i) {
			const auto& [prefix, unit, exp] = val.unit[i];
			if (i) {
				if (exp > 0) {
					out << "*";
				}
				else {
					out << "/";
				}
			}
			std::unordered_map<unit_prefix, std::string>::const_iterator prefix_it = prefix_str_map.find(prefix);
			if (prefix_it == prefix_str_map.end()) {
				throw std::runtime_error("operator<<(std::ostream&, const genev&): unknown prefix");
			}
			out << prefix_it->second;
			std::unordered_map<base_unit, std::string>::const_iterator unit_it = unit_str_map.find(unit);
			if (unit_it == unit_str_map.end()) {
				throw std::runtime_error("operator<<(std::ostream&, const genev&): unknown unit");
			}
			out << unit_it->second;
			long long exp_abs = std::abs(exp);
			if (exp_abs != 1 || (exp == -1 && !i)) {
				out << "^";
				if (i) {
					out << exp_abs;
				}
				else {
					out << exp;
				}
			}
		}
		return out;
	}

	std::istream& operator>>(std::istream& in, genev& val) {
		std::string value, unit;
		in >> value >> unit;
		val = genev(value + " " + unit);
		return in;
	}

	genev unify(const genev& orig) {
		genev unified = orig;
		for (auto& [prefix, unit, exp] : unified.unit) {
			std::unordered_map<unit_prefix, signed char>::const_iterator unit_it = prefix_exp_map.find(prefix);
			if (unit_it == prefix_exp_map.end()) {
				throw std::runtime_error("unify: unknown prefix");
			}
			if (unit == base_unit::g) {
				unified.value *= std::pow(10, (unit_it->second - 3) * exp);
				prefix = unit_prefix::k;
			}
			else {
				unified.value *= std::pow(10, unit_it->second * exp);
				prefix = unit_prefix::none;
			}
		}
		return unified;
	}

	genev simplify(const genev& orig) {
		genev simplified = unify(orig);
		std::unordered_map<base_unit, long long> exp_map;
		for (const auto& [_, unit, exp] : simplified.unit) {
			exp_map[unit] += exp;
		}
		simplified.unit.clear();
		for (const auto& [unit, exp] : exp_map) {
			if (exp) {
				if (unit == base_unit::g) {
					simplified.unit.push_back({ unit_prefix::k, unit, exp });
				}
				else {
					simplified.unit.push_back({ unit_prefix::none, unit, exp });
				}
			}
		}
		return simplified;
	}

	genev convert(const genev& orig, const std::string& new_unit) {
		genev converted("1 " + new_unit);
		if (!converted.same_unit(orig)) {
			throw std::runtime_error("convert: type mismatch");
		}
		converted.value = unify(orig).value;
		for (const auto& [prefix, _, exp] : converted.unit) {
			std::unordered_map<unit_prefix, signed char>::const_iterator unit_it = prefix_exp_map.find(prefix);
			if (unit_it == prefix_exp_map.end()) {
				throw std::runtime_error("convert: unknown prefix");
			}
			converted.value /= pow(10, unit_it->second * exp);
		}
		return converted;
	}
}