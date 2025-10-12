#include "hedgehog_impl.h"
#include "hedgehog_iterators.h"

namespace launch {
	bool oper_sign::operator==(const oper_sign& other) const {
		return lhs == other.lhs && oper == other.oper && rhs == other.rhs;
	}

	hedgehog_regtable hregtable{};

	void hedgehog_regtable::regtype_output(std::type_index key, std::function<std::ostream&(std::ostream&, const std::any&)> func) {
		std::unique_lock lock(output_mutex_);
		output_reg[key] = func;
	}

	void hedgehog_regtable::regtype_oper(oper_sign key, std::function<std::any(std::any, std::any)> func) {
		std::unique_lock lock(oper_mutex_);
		oper_reg[key] = func;
	}

	hedgehog_regtable::hedgehog_regtable() {
		regtype_output(typeid(bool), [](std::ostream& out, const std::any& value) -> std::ostream& {
			return out << (std::any_cast<bool>(value) ? "true" : "false");
		});
		regtype_output_auto<short>();
		regtype_5ops_auto<short>();
		regtype_output_auto<int>();
		regtype_5ops_auto<int>();
		regtype_output_auto<long long>();
		regtype_5ops_auto<long long>();
		regtype_output_auto<float>();
		regtype_4ops_auto<float>();
		regtype_output_auto<double>();
		regtype_4ops_auto<double>();
		regtype_output_auto<char>();
		regtype_output_auto<const char*>();
		regtype_output_auto<std::string>();
		regtype_add_auto<std::string>();
#if !defined(LAUNCH_NO_GOODSTR)
		regtype_output_auto<hstr>();
		regtype_add_auto<hstr>();
#endif
	}

	const std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>& hedgehog_regtable::get_output() const {
		std::shared_lock lock(output_mutex_);
		return output_reg;
	}

	const std::unordered_map<oper_sign, std::function<std::any(std::any, std::any)>>& hedgehog_regtable::get_oper() const {
		std::shared_lock lock(oper_mutex_);
		return oper_reg;
	}

	std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>::const_iterator hedgehog_regtable::output_func_it(std::type_index key) const {
		std::shared_lock lock(output_mutex_);
		return output_reg.find(key);
	}

	std::unordered_map<oper_sign, std::function<std::any(std::any, std::any)>>::const_iterator hedgehog_regtable::oper_func_it(oper_sign key) const {
		std::shared_lock lock(oper_mutex_);
		return oper_reg.find(key);
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator=(const std::any& _value) {
		value = _value;
		return *this;
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator+=(const std::any& _value) {
		if (!_value.has_value()) {
			throw std::invalid_argument("Empty Operand");
		}
		const std::type_info& type = _value.type();
		std::unordered_map<oper_sign, std::function<std::any(std::any, std::any)>>::const_iterator func_it = hregtable.oper_func_it({value.type(), oper_type::add, type});
		if (func_it != hregtable.get_oper().end()) {
			value = (func_it->second)(value, _value);
			return *this;
		}
		throw std::runtime_error("No Such Operator");
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator-=(const std::any& _value) {
		if (!_value.has_value()) {
			throw std::invalid_argument("Empty Operand");
		}
		const std::type_info& type = _value.type();
		std::unordered_map<oper_sign, std::function<std::any(std::any, std::any)>>::const_iterator func_it = hregtable.oper_func_it({value.type(), oper_type::sub, type});
		if (func_it != hregtable.get_oper().end()) {
			value = (func_it->second)(value, _value);
			return *this;
		}
		throw std::runtime_error("No Such Operator");
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator*=(const std::any& _value) {
		if (!_value.has_value()) {
			throw std::invalid_argument("Empty Operand");
		}
		const std::type_info& type = _value.type();
		std::unordered_map<oper_sign, std::function<std::any(std::any, std::any)>>::const_iterator func_it = hregtable.oper_func_it({value.type(), oper_type::mul, type});
		if (func_it != hregtable.get_oper().end()) {
			value = (func_it->second)(value, _value);
			return *this;
		}
		throw std::runtime_error("No Such Operator");
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator/=(const std::any& _value) {
		if (!_value.has_value()) {
			throw std::invalid_argument("Empty Operand");
		}
		const std::type_info& type = _value.type();
		std::unordered_map<oper_sign, std::function<std::any(std::any, std::any)>>::const_iterator func_it = hregtable.oper_func_it({value.type(), oper_type::div, type});
		if (func_it != hregtable.get_oper().end()) {
			value = (func_it->second)(value, _value);
			return *this;
		}
		throw std::runtime_error("No Such Operator");
	}

	hedgehog_elemproxy& hedgehog_elemproxy::operator%=(const std::any& _value) {
		if (!_value.has_value()) {
			throw std::invalid_argument("Empty Operand");
		}
		const std::type_info& type = _value.type();
		std::unordered_map<oper_sign, std::function<std::any(std::any, std::any)>>::const_iterator func_it = hregtable.oper_func_it({value.type(), oper_type::mod, type});
		if (func_it != hregtable.get_oper().end()) {
			value = (func_it->second)(value, _value);
			return *this;
		}
		throw std::runtime_error("No Such Operator");
	}

	std::ostream& operator<<(std::ostream& out, const hedgehog_elemproxy& proxy) {
		const std::any& _value = proxy.value;
		if (!_value.has_value()) {
			return out << "[EMPTY]";
		}
		const std::type_info& type = _value.type();
		std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>::const_iterator func_it = hregtable.output_func_it(type);
		if (func_it != hregtable.get_output().end()) {
			return (func_it->second)(out, _value);
		}
		return out << "[UNKTYP:" << type.name() << "]";
	}

	hedgehog::hedgehog(std::initializer_list<std::any> init_list) {
		vec.reserve(init_list.size());
		for (const std::any& elem : init_list) {
			vec.push_back(elem);
		}
	}

	hedgehog_elemproxy& hedgehog::operator[](int index) {
		return vec.at(index);
	}

	const hedgehog_elemproxy& hedgehog::operator[](int index) const {
		return vec.at(index);
	}

	hedgehog_iterator hedgehog::begin() {
		return hedgehog_iterator(this, 0);
	}

	hedgehog_iterator hedgehog::end() {
		return hedgehog_iterator(this, vec.size());
	}

	hedgehog_const_iterator hedgehog::begin() const {
		return hedgehog_const_iterator(this, 0);
	}

	hedgehog_const_iterator hedgehog::end() const {
		return hedgehog_const_iterator(this, vec.size());
	}

	hedgehog_const_iterator hedgehog::cbegin() const {
		return hedgehog_const_iterator(this, 0);
	}

	hedgehog_const_iterator hedgehog::cend() const {
		return hedgehog_const_iterator(this, vec.size());
	}

	size_t hedgehog::size() const {
		return vec.size();
	}

	size_t hedgehog::capacity() const {
		return vec.capacity();
	}

	size_t hedgehog::avail_size() const {
		return this->capacity() - this->size();
	}

	bool hedgehog::empty() const {
		return vec.empty();
	}

	void hedgehog::reserve_more(int n) {
		vec.reserve(this->capacity() + n);
	}

	bool hedgehog::shrink_to_fit() {
		size_t _capacity = this->capacity();
		vec.shrink_to_fit();
		return _capacity != this->capacity();
	}

	void hedgehog::push_back(std::any value) {
		vec.push_back(value);
	}

	void hedgehog::erase(int index) {
		vec.erase(vec.begin() + index);
	}

	hedgehog_elemproxy hedgehog::get(int index) const {
		return (*this)[index];
	}

	void hedgehog::clear() {
		vec.clear();
		this->shrink_to_fit();
	}

	void hedgehog::insert(std::any value, int pos) {
		vec.insert(vec.begin() + pos, value);
	}

	void hedgehog::fill(std::any value, int count) {
		this->reserve_more(count);
		for (int i = 0; i < count; ++i) {
			vec.push_back(value);
		}
	}
}