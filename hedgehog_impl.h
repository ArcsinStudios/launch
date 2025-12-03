#pragma once

#include <any>
#include <functional>
#include <initializer_list>
#include <iostream>

#if !defined(LAUNCH_NO_THREAD_SAFE)
#include <shared_mutex>
#endif

#include <stdexcept>
#include <typeindex>
#include <unordered_map>
#include <vector>

#if !defined(LAUNCH_NO_GOODMATH) && defined(LAUNCH_GOODMATH_ARINT)
#include "goodmath.h"
#endif

#if !defined(LAUNCH_NO_GOODSTR)
#include "goodstr.h"
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
	class hedgehog_iterator;
	class hedgehog_const_iterator;

	template <typename T>
	concept Printable = requires(std::ostream& out, const T& value) {
		{ out << value } -> std::same_as<std::ostream&>;
	};

	template <typename T>
	concept Arithmetic_Add = requires(T a, T b) {
		{ a + b } -> std::convertible_to<T>;
	};

	template <typename T>
	concept Arithmetic_Sub = requires(T a, T b) {
		{ a - b } -> std::convertible_to<T>;
	};

	template <typename T>
	concept Arithmetic_Mul = requires(T a, T b) {
		{ a * b } -> std::convertible_to<T>;
	};

	template <typename T>
	concept Arithmetic_Div = requires(T a, T b) {
		{ a / b } -> std::convertible_to<T>;
	};

	template <typename T>
	concept Arithmetic_Mod = requires(T a, T b) {
		{ a % b } -> std::convertible_to<T>;
	};

	template <typename T>
	concept Arithmetic = Arithmetic_Add<T> && Arithmetic_Sub<T> && Arithmetic_Mul<T> && Arithmetic_Div<T>;

	template <typename T>
	concept Fully_Arithmetic = Arithmetic<T> && Arithmetic_Mod<T>;

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
			output_reg[typeid(T)] = [](std::ostream& out, const std::any& value) -> std::ostream& {
				return out << std::any_cast<T>(value);
			};
		}

		void regtype_oper(hedgehog_opersign key, std::function<std::any(std::any, std::any)> func);

		template <Arithmetic_Add T>
		void regtype_add_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex_);
#endif
			oper_reg[{typeid(T), hedgehog_opertype::add, typeid(T)}] = [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) + std::any_cast<T>(b);
			};
		}

		template <Arithmetic_Sub T>
		void regtype_sub_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex_);
#endif
			oper_reg[{typeid(T), hedgehog_opertype::sub, typeid(T)}] = [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) - std::any_cast<T>(b);
			};
		}

		template <Arithmetic_Mul T>
		void regtype_mul_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex_);
#endif
			oper_reg[{typeid(T), hedgehog_opertype::mul, typeid(T)}] = [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) * std::any_cast<T>(b);
			};
		}

		template <Arithmetic_Div T>
		void regtype_div_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex_);
#endif
			oper_reg[{typeid(T), hedgehog_opertype::div, typeid(T)}] = [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) / std::any_cast<T>(b);
			};
		}

		template <Arithmetic_Mod T>
		void regtype_mod_auto() {
#if !defined(LAUNCH_NO_THREAD_SAFE)
			std::unique_lock lock(oper_mutex_);
#endif
			oper_reg[{typeid(T), hedgehog_opertype::mod, typeid(T)}] = [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) % std::any_cast<T>(b);
			};
		}

		template <Arithmetic T>
		void regtype_4ops_auto() {
			this->regtype_add_auto<T>();
			this->regtype_sub_auto<T>();
			this->regtype_mul_auto<T>();
			this->regtype_div_auto<T>();
		}

		template <Fully_Arithmetic T>
		void regtype_5ops_auto() {
			this->regtype_4ops_auto<T>();
			this->regtype_mod_auto<T>();
		}

		hedgehog_registry();

		const std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>& get_output() const;

		const std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>>& get_oper() const;

		std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>::const_iterator output_func_it(std::type_index key) const;

		std::unordered_map<hedgehog_opersign, std::function<std::any(std::any, std::any)>>::const_iterator oper_func_it(hedgehog_opersign key) const;
	};

	class hedgehog_elemproxy {
	private:
		std::any value;

	public:
		hedgehog_elemproxy(const std::any& _value) : value(_value) {}

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
			if (value.type() != typeid(T)) {
				throw std::runtime_error("Type Assertion Failed");
			}
		}

		template <typename T>
		bool assert_bool() const {
			return value.type() == typeid(T);
		}
	};

	class hedgehog {
	private:
		std::vector<hedgehog_elemproxy> vec;

	public:
		hedgehog(std::initializer_list<std::any> init_list);

		hedgehog_elemproxy& operator[](size_t index);

		const hedgehog_elemproxy& operator[](size_t index) const;

		hedgehog_elemproxy& at(size_t index);

		const hedgehog_elemproxy& at(size_t index) const;

		hedgehog_iterator begin();

		hedgehog_iterator end();

		hedgehog_const_iterator begin() const;

		hedgehog_const_iterator end() const;

		hedgehog_const_iterator cbegin() const;

		hedgehog_const_iterator cend() const;

		hedgehog_elemproxy& front();

		const hedgehog_elemproxy& front() const;

		hedgehog_elemproxy& back();

		const hedgehog_elemproxy& back() const;

		size_t size() const;

		size_t capacity() const;

		bool empty() const;

		void reserve(int n);

		void shrink_to_fit();

		void push_back(std::any value);

		void pop_back();

		void insert(size_t index, std::any value);

		void erase(size_t index);

		void clear();

		template <typename T>
		std::vector<T> filter() {
			std::vector<T> filtered;
			for (const hedgehog_elemproxy& elem : vec) {
				if (elem.assert_bool<T>()) {
					filtered.push_back(elem.as<T>());
				}
			}
			return filtered;
		}
	};

	extern hedgehog_registry hregistry;
}