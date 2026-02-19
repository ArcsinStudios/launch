#pragma once

#include <concepts>
#include <iostream>

namespace launch {
	template <typename T>
	concept writable = requires(std::ostream& os, const T& x) {
		{ os << x } -> std::same_as<std::ostream&>;
	};

	template <typename T>
	concept arithmetic_preq = !std::is_pointer_v<T> && !std::is_same_v<bool, T>;

	template <typename T, typename U>
	concept arithmetic_add =
		requires(T a, U b) {
		a + b;
	} && arithmetic_preq<T> && arithmetic_preq<U>;

	template <typename T, typename U>
	concept arithmetic_sub =
		requires(T a, U b) {
		a - b;
	} && arithmetic_preq<T> && arithmetic_preq<U>;

	template <typename T, typename U>
	concept arithmetic_mul =
		requires(T a, U b) {
		a* b;
	} && arithmetic_preq<T> && arithmetic_preq<U>;

	template <typename T, typename U>
	concept arithmetic_div =
		requires(T a, U b) {
		a / b;
	} && arithmetic_preq<T> && arithmetic_preq<U>;

	template <typename T, typename U>
	concept arithmetic_mod =
		requires(T a, U b) {
		a% b;
	} && arithmetic_preq<T> && arithmetic_preq<U>;

	template <typename T, typename U>
	concept arithmetic = arithmetic_add<T, U> && arithmetic_sub<T, U> && arithmetic_mul<T, U> && arithmetic_div<T, U>;

	template <typename T, typename U>
	concept fully_arithmetic = arithmetic<T, U> && arithmetic_mod<T, U>;
}