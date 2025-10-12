#pragma once

#include <any>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <shared_mutex>
#include <typeindex>
#include <unordered_map>
#include <vector>

#if !defined(LAUNCH_NO_GOODSTR)
#include "goodstr.h"
#endif

namespace launch {
	enum class oper_type {
		add,
		sub,
		mul,
		div,
		mod
	};

	struct oper_sign {
		std::type_index lhs;
		oper_type oper;
		std::type_index rhs;

		bool operator==(const oper_sign& other) const;
	};
}

namespace std {
	template<>
	struct hash<launch::oper_sign> {
		size_t operator()(const launch::oper_sign& sign) const {
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

	class hedgehog_regtable {
	private:
		std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>> output_reg;
		std::unordered_map<oper_sign, std::function<std::any(std::any, std::any)>> oper_reg;
		mutable std::shared_mutex output_mutex_;
		mutable std::shared_mutex oper_mutex_;

	public:
		void regtype_output(std::type_index key, std::function<std::ostream&(std::ostream&, const std::any&)> func);

		template <Printable T>
		void regtype_output_auto() {
			std::unique_lock lock(output_mutex_);
			output_reg[typeid(T)] = [](std::ostream& out, const std::any& value) -> std::ostream& {
				return out << std::any_cast<T>(value);
			};
		}

		void regtype_oper(oper_sign key, std::function<std::any(std::any, std::any)> func);

		template <Arithmetic_Add T>
		void regtype_add_auto() {
			std::unique_lock lock(oper_mutex_);
			oper_reg[{typeid(T), oper_type::add, typeid(T)}] = [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) + std::any_cast<T>(b);
			};
		}

		template <Arithmetic_Sub T>
		void regtype_sub_auto() {
			std::unique_lock lock(oper_mutex_);
			oper_reg[{typeid(T), oper_type::sub, typeid(T)}] = [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) - std::any_cast<T>(b);
			};
		}

		template <Arithmetic_Mul T>
		void regtype_mul_auto() {
			std::unique_lock lock(oper_mutex_);
			oper_reg[{typeid(T), oper_type::mul, typeid(T)}] = [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) * std::any_cast<T>(b);
			};
		}

		template <Arithmetic_Div T>
		void regtype_div_auto() {
			std::unique_lock lock(oper_mutex_);
			oper_reg[{typeid(T), oper_type::div, typeid(T)}] = [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) / std::any_cast<T>(b);
			};
		}

		template <Arithmetic_Mod T>
		void regtype_mod_auto() {
			std::unique_lock lock(oper_mutex_);
			oper_reg[{typeid(T), oper_type::mod, typeid(T)}] = [](std::any a, std::any b) -> std::any {
				return std::any_cast<T>(a) % std::any_cast<T>(b);
			};
		}

		template <Arithmetic T>
		void regtype_4ops_auto() {
			regtype_add_auto<T>();
			regtype_sub_auto<T>();
			regtype_mul_auto<T>();
			regtype_div_auto<T>();
		}

		template <Fully_Arithmetic T>
		void regtype_5ops_auto() {
			regtype_4ops_auto<T>();
			regtype_mod_auto<T>();
		}

		hedgehog_regtable();

		const std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>& get_output() const;

		const std::unordered_map<oper_sign, std::function<std::any(std::any, std::any)>>& get_oper() const;

		std::unordered_map<std::type_index, std::function<std::ostream&(std::ostream&, const std::any&)>>::const_iterator output_func_it(std::type_index key) const;

		std::unordered_map<oper_sign, std::function<std::any(std::any, std::any)>>::const_iterator oper_func_it(oper_sign key) const;
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

		hedgehog_elemproxy& operator[](int index);

		const hedgehog_elemproxy& operator[](int index) const;

		hedgehog_iterator begin();

		hedgehog_iterator end();

		hedgehog_const_iterator begin() const;

		hedgehog_const_iterator end() const;

		hedgehog_const_iterator cbegin() const;

		hedgehog_const_iterator cend() const;

		size_t spines() const;

		size_t max_spines() const;

		size_t avail_spines() const;

		bool empty() const;

		void puff(int n);

		bool quill();

		void stick(std::any value);

		void take(int index);

		hedgehog_elemproxy get(int index) const;

		void clear();

		void insert(std::any value, int pos);

		void fill(std::any value, int count);
	};
}