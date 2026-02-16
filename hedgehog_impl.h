#pragma once

#include <any>
#include <concepts>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

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
			size_t h1 = hash<type_index>{}(sign.lhs);
			size_t h2 = hash<int>{}(static_cast<int>(sign.oper));
			size_t h3 = hash<type_index>{}(sign.rhs);
			return h1 ^ (h2 << 1) ^ (h3 << 2);
		}
	};
}

namespace launch {
	template <typename T>
	concept Printable = requires(std::ostream& out, const T& value) {
		{ out << value } -> std::same_as<std::ostream&>;
	};

	template <typename T, typename U>
	concept ArithmeticAdd =
		requires(T a, U b) {
			a + b;
		} &&
		!std::is_pointer_v<T> && !std::is_pointer_v<U> &&
		!std::is_same_v<T, bool> && !std::is_same_v<U, bool>;

	template <typename T, typename U>
	concept ArithmeticSub =
		requires(T a, U b) {
			a - b;
		} &&
		!std::is_pointer_v<T> && !std::is_pointer_v<U> &&
		!std::is_same_v<T, bool> && !std::is_same_v<U, bool>;

	template <typename T, typename U>
	concept ArithmeticMul =
		requires(T a, U b) {
			a * b;
		} &&
		!std::is_pointer_v<T> && !std::is_pointer_v<U> &&
		!std::is_same_v<T, bool> && !std::is_same_v<U, bool>;

	template <typename T, typename U>
	concept ArithmeticDiv =
		requires(T a, U b) {
			a / b;
		} &&
		!std::is_pointer_v<T> && !std::is_pointer_v<U> &&
		!std::is_same_v<T, bool> && !std::is_same_v<U, bool>;

	template <typename T, typename U>
	concept ArithmeticMod =
		requires(T a, U b) {
			a % b;
		} &&
		!std::is_pointer_v<T> && !std::is_pointer_v<U> &&
		!std::is_same_v<T, bool> && !std::is_same_v<U, bool>;

	template <typename T, typename U>
	concept Arithmetic = ArithmeticAdd<T, U> && ArithmeticSub<T, U> && ArithmeticMul<T, U> && ArithmeticDiv<T, U>;

	template <typename T, typename U>
	concept FullyArithmetic = Arithmetic<T, U> && ArithmeticMod<T, U>;

	class hedgehog_registry {
	private:
		std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>> output_reg;
		std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>> oper_reg;
#if !defined(LAUNCH_NO_THREAD_SAFE)
		mutable std::shared_mutex output_mutex_;
		mutable std::shared_mutex oper_mutex_;
#endif

	public:
		void regtype_output(std::type_index key, std::function<std::ostream&(std::ostream&, const std::any&)> func);

		template <Printable T>
		void regtype_output_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(output_mutex_);
#endif
			this->regtype_output(typeid(T), [](std::ostream& out, const std::any& value) -> std::ostream& {
				return out << std::any_cast<T>(value);
			});
		}

		void regtype_oper(hedgehog_opersign key, std::function<std::any(std::any, std::any)> func);

		template <typename T, typename U = T> requires ArithmeticAdd<T, U>
		void regtype_add_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex_);
#endif
			this->regtype_oper({typeid(T), hedgehog_opertype::add, typeid(U)}, [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) + std::any_cast<U>(b);
			});
		}

		template <typename T, typename U> requires ArithmeticAdd<T, U>
		void regtype_add_auto_rev() {
			this->regtype_add_auto<T, U>();
			this->regtype_add_auto<U, T>();
		}

		template <typename T, typename U = T> requires ArithmeticSub<T, U>
		void regtype_sub_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex_);
#endif
			this->regtype_oper({typeid(T), hedgehog_opertype::sub, typeid(U)}, [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) - std::any_cast<U>(b);
			});
		}

		template <typename T, typename U> requires ArithmeticSub<T, U>
		void regtype_sub_auto_rev() {
			this->regtype_sub_auto<T, U>();
			this->regtype_sub_auto<U, T>();
		}

		template <typename T, typename U = T> requires ArithmeticMul<T, U>
		void regtype_mul_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex_);
#endif
			this->regtype_oper({typeid(T), hedgehog_opertype::mul, typeid(U)}, [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) * std::any_cast<U>(b);
			});
		}

		template <typename T, typename U> requires ArithmeticMul<T, U>
		void regtype_mul_auto_rev() {
			this->regtype_mul_auto<T, U>();
			this->regtype_mul_auto<U, T>();
		}

		template <typename T, typename U = T> requires ArithmeticDiv<T, U>
		void regtype_div_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex_);
#endif
			this->regtype_oper({typeid(T), hedgehog_opertype::div, typeid(U)}, [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) / std::any_cast<U>(b);
			});
		}

		template <typename T, typename U> requires ArithmeticDiv<T, U>
		void regtype_div_auto_rev() {
			this->regtype_div_auto<T, U>();
			this->regtype_div_auto<U, T>();
		}

		template <typename T, typename U = T> requires ArithmeticMod<T, U>
		void regtype_mod_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex_);
#endif
			this->regtype_oper({typeid(T), hedgehog_opertype::mod, typeid(U)}, [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) % std::any_cast<U>(b);
			});
		}

		template <typename T, typename U> requires ArithmeticMod<T, U>
		void regtype_mod_auto_rev() {
			this->regtype_mod_auto<T, U>();
			this->regtype_mod_auto<U, T>();
		}

		template <typename T, typename U = T> requires Arithmetic<T, U>
		void regtype_4ops_auto() {
			this->regtype_add_auto<T, U>();
			this->regtype_sub_auto<T, U>();
			this->regtype_mul_auto<T, U>();
			this->regtype_div_auto<T, U>();
		}

		template <typename T, typename U> requires Arithmetic<T, U>
		void regtype_4ops_auto_rev() {
			this->regtype_add_auto_rev<T, U>();
			this->regtype_sub_auto_rev<T, U>();
			this->regtype_mul_auto_rev<T, U>();
			this->regtype_div_auto_rev<T, U>();
		}

		template <typename T, typename U = T> requires FullyArithmetic<T, U>
		void regtype_5ops_auto() {
			this->regtype_4ops_auto<T, U>();
			this->regtype_mod_auto<T, U>();
		}

		template <typename T, typename U> requires FullyArithmetic<T, U>
		void regtype_5ops_auto_rev() {
			this->regtype_4ops_auto_rev<T, U>();
			this->regtype_mod_auto_rev<T, U>();
		}

		template <typename T, typename U>
		void regtype_helper_process() {
			if constexpr (ArithmeticAdd<T, U>) {
				this->regtype_add_auto_rev<T, U>();
			}
			if constexpr (ArithmeticSub<T, U>) {
				this->regtype_sub_auto_rev<T, U>();
			}
			if constexpr (ArithmeticMul<T, U>) {
				this->regtype_mul_auto_rev<T, U>();
			}
			if constexpr (ArithmeticDiv<T, U>) {
				this->regtype_div_auto_rev<T, U>();
			}
			if constexpr (ArithmeticMod<T, U>) {
				this->regtype_mod_auto_rev<T, U>();
			}
		}

		template <typename T, typename... Us>
		void regtype_helper() {
			if constexpr (Printable<T>) {
				this->regtype_output_auto<T>();
			}
			this->regtype_helper_process<T, T>();
			if constexpr (sizeof...(Us)) {
				(this->regtype_helper_process<T, Us>(), ...);
				this->regtype_helper<Us...>();
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
		template <typename T>
		hedgehog_elemproxy(T _value) : value(std::forward<T>(_value)) {}
		
		hedgehog_elemproxy& operator=(const std::any& _value);

		hedgehog_elemproxy& operator+=(const std::any& _value);

		hedgehog_elemproxy& operator-=(const std::any& _value);

		hedgehog_elemproxy& operator*=(const std::any& _value);

		hedgehog_elemproxy& operator/=(const std::any& _value);

		hedgehog_elemproxy& operator%=(const std::any& _value);

		friend std::ostream& operator<<(std::ostream& out, const hedgehog_elemproxy& proxy);

		template <typename T>
		T as() const {
			return std::any_cast<T>(value);
		}

		template <typename T>
		void assert_strict() const {
			const std::type_info& type0 = value.type();
			const std::type_info& type1 = typeid(T);
			if (type0 != type1) {
				throw std::runtime_error(
					std::string("hedgehog_elemproxy::assert_strict: type0 (mangled name: ") +
					type0.name() +
					") does not match with type1 (mangled name: " +
					type1.name() +
					")"
				);
			}
		}

		template <typename T>
		bool assert_bool() const {
			return value.type() == typeid(T);
		}

		const std::type_info& type() const;
	};

	template <typename Allocator>
	using hedgehog_alloc = std::vector<hedgehog_elemproxy, Allocator>;

	using hedgehog = hedgehog_alloc<std::allocator<hedgehog_elemproxy>>;

	extern hedgehog_registry hregistry;
}