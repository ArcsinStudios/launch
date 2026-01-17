#include "launch_config.h"

#include "hedgehog_impl.h"

namespace launch {
	hedgehog_registry hregistry;

	bool hedgehog_opersign::operator==(const hedgehog_opersign& other) const {
		return lhs == other.lhs && oper == other.oper && rhs == other.rhs;
	}

	void hedgehog_registry::regtype_output(std::type_index key, std::function<std::ostream&(std::ostream&, const std::any&)> func) {
#if !defined(LAUNCH_NO_THREAD_SAFE)
		std::unique_lock lock(output_mutex_);
#endif
		output_reg[key] = func;
	}

	void hedgehog_registry::regtype_oper(hedgehog_opersign key, std::function<std::any(std::any, std::any)> func) {
#if !defined(LAUNCH_NO_THREAD_SAFE)
		std::unique_lock lock(oper_mutex_);
#endif
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
		this->regtype_5ops_auto_rev<short, int>();
		this->regtype_5ops_auto_rev<short, long long>();
		this->regtype_5ops_auto_rev<int, long long>();
		this->regtype_output_auto<float>();
		this->regtype_4ops_auto<float>();
		this->regtype_output_auto<double>();
		this->regtype_4ops_auto<double>();
		this->regtype_4ops_auto_rev<float, double>();
		this->regtype_4ops_auto_rev<float, short>();
		this->regtype_4ops_auto_rev<float, int>();
		this->regtype_4ops_auto_rev<float, long long>();
		this->regtype_4ops_auto_rev<double, short>();
		this->regtype_4ops_auto_rev<double, int>();
		this->regtype_4ops_auto_rev<double, long long>();
		this->regtype_output_auto<char>();
		this->regtype_output_auto<const char*>();
		this->regtype_oper(
			{typeid(const char*), hedgehog_opertype::add, typeid(const char*)},
			[](std::any a, std::any b) -> std::any {
				return std::string(std::any_cast<const char*>(a)) + std::string(std::any_cast<const char*>(b));
			}
		);
		this->regtype_output_auto<std::string>();
		this->regtype_add_auto<std::string>();
		this->regtype_add_auto_rev<std::string, const char*>();
#if !defined(LAUNCH_NO_ESCSEQ)
		this->regtype_output_auto<escseq_manip>();
		this->regtype_output_auto<style_manip>();
		this->regtype_output_auto<reset_endl>();
#endif
#if defined(LAUNCH_EXPERIMENTAL)
		this->regtype_output_auto<leisure::arint>();
		this->regtype_5ops_auto<leisure::arint>();
		this->regtype_output_auto<leisure::arreal>();
		this->regtype_4ops_auto<leisure::arreal>();
#endif
	}

	const std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>& hedgehog_registry::get_output() const {
#if !defined(LAUNCH_NO_THREAD_SAFE)
		std::shared_lock lock(output_mutex_);
#endif
		return output_reg;
	}

	const std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>>& hedgehog_registry::get_oper() const {
#if !defined(LAUNCH_NO_THREAD_SAFE)
		std::shared_lock lock(oper_mutex_);
#endif
		return oper_reg;
	}

	std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>::const_iterator hedgehog_registry::output_func_it(std::type_index key) const {
#if !defined(LAUNCH_NO_THREAD_SAFE)
		std::shared_lock lock(output_mutex_);
#endif
		return output_reg.find(key);
	}

	std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>>::const_iterator hedgehog_registry::oper_func_it(hedgehog_opersign key) const {
#if !defined(LAUNCH_NO_THREAD_SAFE)
		std::shared_lock lock(oper_mutex_);
#endif
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