#pragma once

#include <any>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

#include "hedgehog_concepts.h"

#if !defined(LAUNCH_NO_ESCSEQ)
#include "escseq.h"
#endif

#if defined(LAUNCH_EXPERIMENTAL)
#include "arithing.h"
#endif

namespace launch {
	enum class hedgehog_opertype : unsigned char {
		add,
		sub,
		mul,
		div,
		mod
	};

	struct hedgehog_opersign {
		std::type_index lhs;
		hedgehog_opertype oper;
		std::type_index rhs;

		bool operator==(const hedgehog_opersign& other) const;
	};
}

namespace std {
	template<>
	struct hash<launch::hedgehog_opersign> {
		size_t operator()(const launch::hedgehog_opersign& sign) const {
			size_t h1 = hash<type_index>()(sign.lhs);
			size_t h2 = hash<std::underlying_type_t<launch::hedgehog_opertype>>()
				(static_cast<std::underlying_type_t<launch::hedgehog_opertype>>(sign.oper));
			size_t h3 = hash<type_index>()(sign.rhs);
			return h1 ^ (h2 << 1) ^ (h3 << 2);
		}
	};
}

namespace launch {
	using output_func_t = std::function<std::ostream&(std::ostream&, const std::any&)>;
	using oper_func_t = std::function<std::any(const std::any&, const std::any&)>;
	using output_reg_t = std::unordered_map<std::type_index, output_func_t>;
	using oper_reg_t = std::unordered_map<hedgehog_opersign, oper_func_t>;

	class hedgehog_registry {
	private:
		output_reg_t output_reg;
		oper_reg_t oper_reg;

	public:
		void regtype_output(std::type_index key, output_func_t func);

		void regtype_oper(hedgehog_opersign key, oper_func_t func);

		template <typename T, typename U = T>
		void regtype_add(oper_func_t func) {
			regtype_oper({ typeid(T), hedgehog_opertype::add, typeid(U) }, func);
		}

		template <typename T, typename U = T>
		void regtype_sub(oper_func_t func) {
			regtype_oper({ typeid(T), hedgehog_opertype::sub, typeid(U) }, func);
		}

		template <typename T, typename U = T>
		void regtype_mul(oper_func_t func) {
			regtype_oper({ typeid(T), hedgehog_opertype::mul, typeid(U) }, func);
		}

		template <typename T, typename U = T>
		void regtype_div(oper_func_t func) {
			regtype_oper({ typeid(T), hedgehog_opertype::div, typeid(U) }, func);
		}

		template <typename T, typename U = T>
		void regtype_mod(oper_func_t func) {
			regtype_oper({ typeid(T), hedgehog_opertype::mod, typeid(U) }, func);
		}

		template <writable T>
		void regtype_output_auto() {
			regtype_output(typeid(T), [](std::ostream& out, const std::any& value) -> std::ostream& {
				return out << std::any_cast<T>(value);
			});
		}

		template <typename T, typename U = T> requires arithmetic_add<T, U>
		void regtype_add_auto() {
			regtype_add<T, U>(
				[](const std::any& a, const std::any& b) -> std::any {
					return std::any_cast<T>(a) + std::any_cast<U>(b);
				}
			);
		}

		template <typename T, typename U = T> requires arithmetic_sub<T, U>
		void regtype_sub_auto() {
			regtype_sub<T, U>(
				[](const std::any& a, const std::any& b) -> std::any {
					return std::any_cast<T>(a) - std::any_cast<U>(b);
				}
			);
		}

		template <typename T, typename U = T> requires arithmetic_mul<T, U>
		void regtype_mul_auto() {
			regtype_mul<T, U>(
				[](const std::any& a, const std::any& b) -> std::any {
					return std::any_cast<T>(a) * std::any_cast<U>(b);
				}
			);
		}

		template <typename T, typename U = T> requires arithmetic_div<T, U>
		void regtype_div_auto() {
			regtype_div<T, U>(
				[](const std::any& a, const std::any& b) -> std::any {
					return std::any_cast<T>(a) / std::any_cast<U>(b);
				}
			);
		}

		template <typename T, typename U = T> requires arithmetic_mod<T, U>
		void regtype_mod_auto() {
			regtype_mod<T, U>(
				[](const std::any& a, const std::any& b) -> std::any {
					return std::any_cast<T>(a) % std::any_cast<U>(b);
				}
			);
		}

		template <typename T, typename U = T> requires arithmetic<T, U>
		void regtype_4ops_auto() {
			regtype_add_auto<T, U>();
			regtype_sub_auto<T, U>();
			regtype_mul_auto<T, U>();
			regtype_div_auto<T, U>();
		}

		template <typename T, typename U = T> requires fully_arithmetic<T, U>
		void regtype_5ops_auto() {
			regtype_4ops_auto<T, U>();
			regtype_mod_auto<T, U>();
		}

		template <typename T, typename U> requires arithmetic_add<T, U> && arithmetic_add<U, T>
		void regtype_add_auto_rev() {
			regtype_add_auto<T, U>();
			regtype_add_auto<U, T>();
		}

		template <typename T, typename U> requires arithmetic_sub<T, U> && arithmetic_sub<U, T>
		void regtype_sub_auto_rev() {
			regtype_sub_auto<T, U>();
			regtype_sub_auto<U, T>();
		}

		template <typename T, typename U> requires arithmetic_mul<T, U> && arithmetic_mul<U, T>
		void regtype_mul_auto_rev() {
			regtype_mul_auto<T, U>();
			regtype_mul_auto<U, T>();
		}

		template <typename T, typename U> requires arithmetic_div<T, U> && arithmetic_div<U, T>
		void regtype_div_auto_rev() {
			regtype_div_auto<T, U>();
			regtype_div_auto<U, T>();
		}

		template <typename T, typename U> requires arithmetic_mod<T, U> && arithmetic_mod<U, T>
		void regtype_mod_auto_rev() {
			regtype_mod_auto<T, U>();
			regtype_mod_auto<U, T>();
		}

		template <typename T, typename U> requires arithmetic<T, U> && arithmetic<U, T>
		void regtype_4ops_auto_rev() {
			regtype_add_auto_rev<T, U>();
			regtype_sub_auto_rev<T, U>();
			regtype_mul_auto_rev<T, U>();
			regtype_div_auto_rev<T, U>();
		}

		template <typename T, typename U> requires fully_arithmetic<T, U> && fully_arithmetic<U, T>
		void regtype_5ops_auto_rev() {
			regtype_4ops_auto_rev<T, U>();
			regtype_mod_auto_rev<T, U>();
		}

		template <typename T, typename U>
		void regtype_helper_process() {
			if constexpr (arithmetic_add<T, U>) {
				regtype_add_auto<T, U>();
			}
			if constexpr (arithmetic_add<U, T>) {
				regtype_add_auto<U, T>();
			}
			if constexpr (arithmetic_sub<T, U>) {
				regtype_sub_auto<T, U>();
			}
			if constexpr (arithmetic_sub<U, T>) {
				regtype_sub_auto<U, T>();
			}
			if constexpr (arithmetic_mul<T, U>) {
				regtype_mul_auto<T, U>();
			}
			if constexpr (arithmetic_mul<U, T>) {
				regtype_mul_auto<U, T>();
			}
			if constexpr (arithmetic_div<T, U>) {
				regtype_div_auto<T, U>();
			}
			if constexpr (arithmetic_div<U, T>) {
				regtype_div_auto<U, T>();
			}
			if constexpr (arithmetic_mod<T, U>) {
				regtype_mod_auto<T, U>();
			}
			if constexpr (arithmetic_mod<U, T>) {
				regtype_mod_auto<U, T>();
			}
		}

		template <typename T, typename... Us>
		void regtype_helper() {
			if constexpr (writable<T>) {
				regtype_output_auto<T>();
			}
			regtype_helper_process<T, T>();
			if constexpr (sizeof...(Us)) {
				(regtype_helper_process<T, Us>(), ...);
				regtype_helper<Us...>();
			}
		}

		explicit hedgehog_registry(bool default_regs = false);

		output_reg_t::const_iterator output_func_it(std::type_index key) const;

		oper_reg_t::const_iterator oper_func_it(hedgehog_opersign key) const;

		output_reg_t::const_iterator output_reg_end() const;

		oper_reg_t::const_iterator oper_reg_end() const;
	};

	extern hedgehog_registry common_hreg;

	class hedgehog_elemproxy {
	private:
		std::any value;
		hedgehog_registry* registry;

	public:
		template <typename T>
		hedgehog_elemproxy(T _value) : value(std::forward<T>(_value)), registry(&common_hreg) {}

		hedgehog_elemproxy& operator+=(const hedgehog_elemproxy& other);

		hedgehog_elemproxy& operator-=(const hedgehog_elemproxy& other);

		hedgehog_elemproxy& operator*=(const hedgehog_elemproxy& other);

		hedgehog_elemproxy& operator/=(const hedgehog_elemproxy& other);

		hedgehog_elemproxy& operator%=(const hedgehog_elemproxy& other);

		hedgehog_elemproxy& operator++();

		hedgehog_elemproxy operator++(int);

		hedgehog_elemproxy& operator--();

		hedgehog_elemproxy operator--(int);

		friend std::ostream& operator<<(std::ostream& out, const hedgehog_elemproxy& proxy);

		template <typename T>
		T as() const {
			return std::any_cast<T>(value);
		}

		const std::type_info& type() const;

		template <typename T>
		bool is() const {
			return value.type() == typeid(T);
		}

		template <typename T>
		void throw_if_not() const {
			if (!this->is<T>()) {
				throw std::runtime_error(
					std::string("hedgehog_elemproxy::throw_if_not: value.type() (mangled name: ") +
					value.type().name() +
					") does not match with typeid(T) (mangled name: " +
					typeid(T).name() +
					")"
				);
			}
		}

		void rebind(hedgehog_registry& new_reg);
	};

	template <typename T, typename U>
	requires std::is_same_v<hedgehog_elemproxy, T> || std::is_same_v<hedgehog_elemproxy, U>
	hedgehog_elemproxy operator+(const T& a, const U& b) {
		hedgehog_elemproxy temp = a;
		temp += b;
		return temp;
	}

	template <typename T, typename U>
	requires std::is_same_v<hedgehog_elemproxy, T> || std::is_same_v<hedgehog_elemproxy, U>
	hedgehog_elemproxy operator-(const T& a, const U& b) {
		hedgehog_elemproxy temp = a;
		temp -= b;
		return temp;
	}

	template <typename T, typename U>
	requires std::is_same_v<hedgehog_elemproxy, T> || std::is_same_v<hedgehog_elemproxy, U>
	hedgehog_elemproxy operator*(const T& a, const U& b) {
		hedgehog_elemproxy temp = a;
		temp *= b;
		return temp;
	}

	template <typename T, typename U>
	requires std::is_same_v<hedgehog_elemproxy, T> || std::is_same_v<hedgehog_elemproxy, U>
	hedgehog_elemproxy operator/(const T& a, const U& b) {
		hedgehog_elemproxy temp = a;
		temp /= b;
		return temp;
	}

	template <typename T, typename U>
	requires std::is_same_v<hedgehog_elemproxy, T> || std::is_same_v<hedgehog_elemproxy, U>
	hedgehog_elemproxy operator%(const T& a, const U& b) {
		hedgehog_elemproxy temp = a;
		temp %= b;
		return temp;
	}

	template <typename T>
	using hedgehog_impl = std::vector<hedgehog_elemproxy, T>;

	using hedgehog = hedgehog_impl<std::allocator<hedgehog_elemproxy>>;

	template <typename T>
	void rebind_all(hedgehog_impl<T>& cont, hedgehog_registry& new_reg) {
		for (hedgehog_elemproxy& elem : cont) {
			elem.rebind(new_reg);
		}
	}
}