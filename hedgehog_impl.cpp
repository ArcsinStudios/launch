#include "hedgehog_impl.h"

namespace launch {
	hedgehog_registry hregistry;

	bool hedgehog_opersign::operator==(const hedgehog_opersign& other) const {
		return lhs == other.lhs && oper == other.oper && rhs == other.rhs;
	}

	void hedgehog_registry::regtype_output(std::type_index key, std::function<std::ostream&(std::ostream&, const std::any&)> func) {
		std::unique_lock lock(output_mutex_);
		output_reg[key] = func;
	}

	void hedgehog_registry::regtype_oper(hedgehog_opersign key, std::function<std::any(std::any, std::any)> func) {
		std::unique_lock lock(oper_mutex_);
		oper_reg[key] = func;
	}

	hedgehog_registry::hedgehog_registry() {
		this->regtype_output(typeid(bool), [](std::ostream& out, const std::any& value) -> std::ostream& {
			return out << (std::any_cast<bool>(value) ? "true" : "false");
		});
		this->regtype_output_auto<short>();
		this->regtype_5ops_auto<short>();
		this->regtype_output_auto<int>();
		this->regtype_5ops_auto<int>();
		this->regtype_output_auto<long long>();
		this->regtype_5ops_auto<long long>();
		this->regtype_output_auto<float>();
		this->regtype_4ops_auto<float>();
		this->regtype_output_auto<double>();
		this->regtype_4ops_auto<double>();
		this->regtype_output_auto<char>();
		this->regtype_output_auto<const char*>();
		this->regtype_output_auto<std::string>();
		this->regtype_add_auto<std::string>();
#if !defined(LAUNCH_NO_GOODMATH) && defined(LAUNCH_GOODMATH_ARINT)
		this->regtype_output_auto<arint>();
		this->regtype_5ops_auto<arint>();
#endif
#if !defined(LAUNCH_NO_GOODSTR)
		this->regtype_output_auto<std::string>();
		this->regtype_add_auto<std::string>();
#endif
	}

	const std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>& hedgehog_registry::get_output() const {
		std::shared_lock lock(output_mutex_);
		return output_reg;
	}

	const std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>>& hedgehog_registry::get_oper() const {
		std::shared_lock lock(oper_mutex_);
		return oper_reg;
	}

	std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>::const_iterator hedgehog_registry::output_func_it(std::type_index key) const {
		std::shared_lock lock(output_mutex_);
		return output_reg.find(key);
	}

	std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>>::const_iterator hedgehog_registry::oper_func_it(hedgehog_opersign key) const {
		std::shared_lock lock(oper_mutex_);
		return oper_reg.find(key);
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator=(const std::any& _value) {
		value = _value;
		return *this;
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator+=(const std::any& _value) {
		if (!_value.has_value()) {
			throw std::invalid_argument("hedgehog_elemproxy::operator+=: _value.has_value() == false");
		}
		const std::type_info& type0 = value.type();
		const std::type_info& type1 = _value.type();
		std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>>::const_iterator func_it = hregistry.oper_func_it({value.type(), hedgehog_opertype::add, type1});
		if (func_it != hregistry.get_oper().end()) {
			value = (func_it->second)(value, _value);
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

	hedgehog_elemproxy& hedgehog_elemproxy::operator-=(const std::any& _value) {
		if (!_value.has_value()) {
			throw std::invalid_argument("hedgehog_elemproxy::operator-=: _value.has_value() == false");
		}
		const std::type_info& type0 = value.type();
		const std::type_info& type1 = _value.type();
		std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>>::const_iterator func_it = hregistry.oper_func_it({value.type(), hedgehog_opertype::sub, type1});
		if (func_it != hregistry.get_oper().end()) {
			value = (func_it->second)(value, _value);
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

	hedgehog_elemproxy& hedgehog_elemproxy::operator*=(const std::any& _value) {
		if (!_value.has_value()) {
			throw std::invalid_argument("hedgehog_elemproxy::operator*=: _value.has_value() == false");
		}
		const std::type_info& type0 = value.type();
		const std::type_info& type1 = _value.type();
		std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>>::const_iterator func_it = hregistry.oper_func_it({value.type(), hedgehog_opertype::mul, type1});
		if (func_it != hregistry.get_oper().end()) {
			value = (func_it->second)(value, _value);
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

	hedgehog_elemproxy& hedgehog_elemproxy::operator/=(const std::any& _value) {
		if (!_value.has_value()) {
			throw std::invalid_argument("hedgehog_elemproxy::operator/=: _value.has_value() == false");
		}
		const std::type_info& type0 = value.type();
		const std::type_info& type1 = _value.type();
		std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>>::const_iterator func_it = hregistry.oper_func_it({value.type(), hedgehog_opertype::div, type1});
		if (func_it != hregistry.get_oper().end()) {
			value = (func_it->second)(value, _value);
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

	hedgehog_elemproxy& hedgehog_elemproxy::operator%=(const std::any& _value) {
		if (!_value.has_value()) {
			throw std::invalid_argument("hedgehog_elemproxy::operator%=: _value.has_value() == false");
		}
		const std::type_info& type0 = value.type();
		const std::type_info& type1 = _value.type();
		std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>>::const_iterator func_it = hregistry.oper_func_it({value.type(), hedgehog_opertype::mod, type1});
		if (func_it != hregistry.get_oper().end()) {
			value = (func_it->second)(value, _value);
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

	std::ostream& operator<<(std::ostream& out, const hedgehog_elemproxy& proxy) {
		const std::any& _value = proxy.value;
		if (!_value.has_value()) {
			return out << "[EMPTY]";
		}
		const std::type_info& type = _value.type();
		std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>::const_iterator func_it = hregistry.output_func_it(type);
		if (func_it != hregistry.get_output().end()) {
			return (func_it->second)(out, _value);
		}
		return out << "[UNKTYP:" << type.name() << "]";
	}
}