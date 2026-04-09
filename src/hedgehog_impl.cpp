#include "../include/launch_config.h"

#include "../include/hedgehog_impl.h"

namespace launch {
	bool hedgehog_opersign::operator==(const hedgehog_opersign& other) const {
		return lhs == other.lhs && oper == other.oper && rhs == other.rhs;
	}

	void hedgehog_registry::regtype_output(std::type_index key, output_func_t func) {
		output_reg[key] = func;
	}

	void hedgehog_registry::regtype_oper(hedgehog_opersign key, oper_func_t func) {
		oper_reg[key] = func;
	}

	hedgehog_registry::hedgehog_registry(bool default_regs) {
		if (default_regs) {
			regtype_helper<
				signed char, short, int, long long,
				unsigned char, unsigned short, unsigned int, unsigned long long,
				float, double,
				bool, char,
				const char*, std::string
			>();
#if !defined(LAUNCH_NO_ESCSEQ)
			regtype_helper<escseq_manip, style_manip, reset_endl>();
#endif
#if defined(LAUNCH_EXPERIMENTAL)
			regtype_helper<leisure::arint, leisure::arreal>();
#endif
		}
	}

	output_reg_t::const_iterator hedgehog_registry::output_func_it(std::type_index key) const {
		return output_reg.find(key);
	}

	oper_reg_t::const_iterator hedgehog_registry::oper_func_it(hedgehog_opersign key) const {
		return oper_reg.find(key);
	}
	
	output_reg_t::const_iterator hedgehog_registry::output_reg_end() const {
		return output_reg.end();
	}

	oper_reg_t::const_iterator hedgehog_registry::oper_reg_end() const {
		return oper_reg.end();
	}

	hedgehog_registry common_hreg(true);

	hedgehog_elemproxy& hedgehog_elemproxy::operator+=(const hedgehog_elemproxy& other) {
		const std::any& other_value = other.value;
		if (!other_value.has_value()) {
			throw std::invalid_argument("hedgehog_elemproxy::operator+=: other_value.has_value() == false");
		}
		const std::type_info& type0 = value.type();
		const std::type_info& type1 = other_value.type();
		oper_reg_t::const_iterator func_it = registry->oper_func_it({ type0, hedgehog_opertype::add, type1 });
		if (func_it != registry->oper_reg_end()) {
			value = (func_it->second)(value, other_value);
			return *this;
		}
		throw std::runtime_error(
			std::string("hedgehog_elemproxy::operator+=: no such operator registered between type0 (mangled name: ") +
			type0.name() +
			") and type1 (mangled name: "
			+ type1.name() +
			")"
		);
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator-=(const hedgehog_elemproxy& other) {
		const std::any& other_value = other.value;
		if (!other_value.has_value()) {
			throw std::invalid_argument("hedgehog_elemproxy::operator-=: other_value.has_value() == false");
		}
		const std::type_info& type0 = value.type();
		const std::type_info& type1 = other_value.type();
		oper_reg_t::const_iterator func_it = registry->oper_func_it({ type0, hedgehog_opertype::sub, type1 });
		if (func_it != registry->oper_reg_end()) {
			value = (func_it->second)(value, other_value);
			return *this;
		}
		throw std::runtime_error(
			std::string("hedgehog_elemproxy::operator-=: no such operator registered between type0 (mangled name: ") +
			type0.name() +
			") and type1 (mangled name: " +
			type1.name() +
			")"
		);
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator*=(const hedgehog_elemproxy& other) {
		const std::any& other_value = other.value;
		if (!other_value.has_value()) {
			throw std::invalid_argument("hedgehog_elemproxy::operator*=: other_value.has_value() == false");
		}
		const std::type_info& type0 = value.type();
		const std::type_info& type1 = other_value.type();
		oper_reg_t::const_iterator func_it = registry->oper_func_it({ type0, hedgehog_opertype::mul, type1 });
		if (func_it != registry->oper_reg_end()) {
			value = (func_it->second)(value, other_value);
			return *this;
		}
		throw std::runtime_error(
			std::string("hedgehog_elemproxy::operator*=: no such operator registered between type0 (mangled name: ") +
			type0.name() +
			") and type1 (mangled name: " +
			type1.name() +
			")"
		);
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator/=(const hedgehog_elemproxy& other) {
		const std::any& other_value = other.value;
		if (!other_value.has_value()) {
			throw std::invalid_argument("hedgehog_elemproxy::operator/=: other_value.has_value() == false");
		}
		const std::type_info& type0 = value.type();
		const std::type_info& type1 = other_value.type();
		oper_reg_t::const_iterator func_it = registry->oper_func_it({ type0, hedgehog_opertype::div, type1 });
		if (func_it != registry->oper_reg_end()) {
			value = (func_it->second)(value, other_value);
			return *this;
		}
		throw std::runtime_error(
			std::string("hedgehog_elemproxy::operator/=: no such operator registered between type0 (mangled name: ") +
			type0.name() +
			") and type1 (mangled name: " +
			type1.name() +
			")"
		);
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator%=(const hedgehog_elemproxy& other) {
		const std::any& other_value = other.value;
		if (!other_value.has_value()) {
			throw std::invalid_argument("hedgehog_elemproxy::operator%=: other_value.has_value() == false");
		}
		const std::type_info& type0 = value.type();
		const std::type_info& type1 = other_value.type();
		oper_reg_t::const_iterator func_it = registry->oper_func_it({ type0, hedgehog_opertype::mod, type1 });
		if (func_it != registry->oper_reg_end()) {
			value = (func_it->second)(value, other_value);
			return *this;
		}
		throw std::runtime_error(
			std::string("hedgehog_elemproxy::operator%=: no such operator registered between type0 (mangled name: ") +
			type0.name() +
			") and type1 (mangled name: " +
			type1.name() +
			")"
		);
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator++() {
		*this += 1;
		return *this;
	}

	hedgehog_elemproxy hedgehog_elemproxy::operator++(int) {
		hedgehog_elemproxy temp = *this;
		++*this;
		return temp;
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator--() {
		*this -= 1;
		return *this;
	}

	hedgehog_elemproxy hedgehog_elemproxy::operator--(int) {
		hedgehog_elemproxy temp = *this;
		++*this;
		return temp;
	}

	const std::type_info& hedgehog_elemproxy::type() const {
		return value.type();
	}

	void hedgehog_elemproxy::rebind(hedgehog_registry& new_reg) {
		registry = &new_reg;
	}

	std::ostream& operator<<(std::ostream& out, const hedgehog_elemproxy& proxy) {
		const std::any& proxy_value = proxy.value;
		if (!proxy_value.has_value()) {
			throw std::runtime_error("operator<<(std::ostream&, const hedgehog_elemproxy&): proxy_value.has_value() == false");
		}
		const std::type_info& type = proxy_value.type();
		output_reg_t::const_iterator func_it = proxy.registry->output_func_it(type);
		if (func_it != proxy.registry->output_reg_end()) {
			return (func_it->second)(out, proxy_value);
		}
		throw std::runtime_error(
			std::string("operator<<(std::ostream&, const hedgehog_elemproxy&): unknown type (mangled name: ") +
			type.name() +
			")"
		);
	}
}