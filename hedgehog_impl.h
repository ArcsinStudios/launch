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

#if !defined(LAUNCH_NO_THREAD_SAFE)
#include <shared_mutex>
#endif

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
	class hedgehog_registry {
	private:
		std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>> output_reg;
		std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>> oper_reg;
#if !defined(LAUNCH_NO_THREAD_SAFE)
		mutable std::shared_mutex output_mutex;
		mutable std::shared_mutex oper_mutex;
#endif

	public:
		void regtype_output(std::type_index key, std::function<std::ostream&(std::ostream&, const std::any&)> func);

		template <writable T>
		void regtype_output_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(output_mutex);
#endif
			regtype_output(typeid(T), [](std::ostream& out, const std::any& value) -> std::ostream& {
				return out << std::any_cast<T>(value);
			});
		}

		void regtype_oper(hedgehog_opersign key, std::function<std::any(std::any, std::any)> func);

		template <typename T, typename U = T> requires arithmetic_add<T, U>
		void regtype_add_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex);
#endif
			regtype_oper({ typeid(T), hedgehog_opertype::add, typeid(U) }, [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) + std::any_cast<U>(b);
			});
		}

		template <typename T, typename U> requires arithmetic_add<T, U> && arithmetic_add<U, T>
		void regtype_add_auto_rev() {
			regtype_add_auto<T, U>();
			regtype_add_auto<U, T>();
		}

		template <typename T, typename U = T> requires arithmetic_sub<T, U>
		void regtype_sub_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex);
#endif
			regtype_oper({ typeid(T), hedgehog_opertype::sub, typeid(U) }, [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) - std::any_cast<U>(b);
			});
		}

		template <typename T, typename U> requires arithmetic_sub<T, U> && arithmetic_sub<U, T>
		void regtype_sub_auto_rev() {
			regtype_sub_auto<T, U>();
			regtype_sub_auto<U, T>();
		}

		template <typename T, typename U = T> requires arithmetic_mul<T, U>
		void regtype_mul_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex);
#endif
			regtype_oper({ typeid(T), hedgehog_opertype::mul, typeid(U) }, [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) * std::any_cast<U>(b);
			});
		}

		template <typename T, typename U> requires arithmetic_mul<T, U> && arithmetic_mul<U, T>
		void regtype_mul_auto_rev() {
			regtype_mul_auto<T, U>();
			regtype_mul_auto<U, T>();
		}

		template <typename T, typename U = T> requires arithmetic_div<T, U>
		void regtype_div_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex);
#endif
			regtype_oper({ typeid(T), hedgehog_opertype::div, typeid(U) }, [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) / std::any_cast<U>(b);
			});
		}

		template <typename T, typename U> requires arithmetic_div<T, U> && arithmetic_div<U, T>
		void regtype_div_auto_rev() {
			regtype_div_auto<T, U>();
			regtype_div_auto<U, T>();
		}

		template <typename T, typename U = T> requires arithmetic_mod<T, U>
		void regtype_mod_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex);
#endif
			regtype_oper({ typeid(T), hedgehog_opertype::mod, typeid(U) }, [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) % std::any_cast<U>(b);
			});
		}

		template <typename T, typename U> requires arithmetic_mod<T, U> && arithmetic_mod<U, T>
		void regtype_mod_auto_rev() {
			regtype_mod_auto<T, U>();
			regtype_mod_auto<U, T>();
		}

		template <typename T, typename U = T> requires arithmetic<T, U>
		void regtype_4ops_auto() {
			regtype_add_auto<T, U>();
			regtype_sub_auto<T, U>();
			regtype_mul_auto<T, U>();
			regtype_div_auto<T, U>();
		}

		template <typename T, typename U> requires arithmetic<T, U> && arithmetic<U, T>
		void regtype_4ops_auto_rev() {
			regtype_add_auto_rev<T, U>();
			regtype_sub_auto_rev<T, U>();
			regtype_mul_auto_rev<T, U>();
			regtype_div_auto_rev<T, U>();
		}

		template <typename T, typename U = T> requires fully_arithmetic<T, U>
		void regtype_5ops_auto() {
			regtype_4ops_auto<T, U>();
			regtype_mod_auto<T, U>();
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

		hedgehog_registry();

		std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>::const_iterator output_func_it(std::type_index key) const;

		std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>>::const_iterator oper_func_it(hedgehog_opersign key) const;

		std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>::const_iterator output_end() const;

		std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>>::const_iterator oper_end() const;
	};

	class hedgehog_elemproxy {
	private:
		std::any value;

	public:
		hedgehog_elemproxy() = default;

		template <typename T>
		hedgehog_elemproxy(T _value) : value(std::forward<T>(_value)) {}

		hedgehog_elemproxy& operator+=(const hedgehog_elemproxy& other);

		hedgehog_elemproxy& operator-=(const hedgehog_elemproxy& other);

		hedgehog_elemproxy& operator*=(const hedgehog_elemproxy& other);

		hedgehog_elemproxy& operator/=(const hedgehog_elemproxy& other);

		hedgehog_elemproxy& operator%=(const hedgehog_elemproxy& other);

		hedgehog_elemproxy operator+(const hedgehog_elemproxy& other);

		hedgehog_elemproxy operator-(const hedgehog_elemproxy& other);

		hedgehog_elemproxy operator*(const hedgehog_elemproxy& other);

		hedgehog_elemproxy operator/(const hedgehog_elemproxy& other);

		hedgehog_elemproxy operator%(const hedgehog_elemproxy& other);

		friend std::ostream& operator<<(std::ostream& out, const hedgehog_elemproxy& proxy);

		const std::type_info& type() const;

		template <typename T>
		T as() const {
			return std::any_cast<T>(value);
		}

		template <typename T>
		bool is() const {
			return value.type() == typeid(T);
		}

		template <typename T>
		void throw_if_not() const {
			const std::type_info& type0 = value.type();
			const std::type_info& type1 = typeid(T);
			if (type0 != type1) {
				throw std::runtime_error(
					std::string("hedgehog_elemproxy::throw_if_not: type0 (mangled name: ") +
					type0.name() +
					") does not match with type1 (mangled name: " +
					type1.name() +
					")"
				);
			}
		}
	};

	template <typename Allocator>
	using hedgehog_alloc = std::vector<hedgehog_elemproxy, Allocator>;

	using hedgehog = hedgehog_alloc<std::allocator<hedgehog_elemproxy>>;

	extern hedgehog_registry hregistry;
}