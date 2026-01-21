#include "launch_config.h"

#include "goodmath_impl.h"

namespace launch {
	double abs(double x) {
		return std::abs(x);
	}

	double floor(double x) {
		return std::floor(x);
	}

	double ceil(double x) {
		return std::ceil(x);
	}

	double round(double x) {
		return std::round(x);
	}

	double trunc(double x) {
		return std::trunc(x);
	}

	long long floor_ll(double x) {
		return static_cast<long long>(floor(x));
	}

	long long ceil_ll(double x) {
		return static_cast<long long>(ceil(x));
	}

	long long round_ll(double x) {
		return static_cast<long long>(round(x));
	}

	long long trunc_ll(double x) {
		return static_cast<long long>(trunc(x));
	}

	double max(double x, double y) {
		return std::max(x, y);
	}

	double min(double x, double y) {
		return std::min(x, y);
	}

	double pow(double x, double y) {
		return std::pow(x, y);
	}

	double mod(double x, double y) {
		return std::fmod(x, y);
	}

	long long gcd(long long x, long long y) {
		return std::gcd(x, y);
	}

	long long lcm(long long x, long long y) {
		return std::lcm(x, y);
	}

	double sqrt(double x) {
		return std::sqrt(x);
	}

	double cbrt(double x) {
		return std::cbrt(x);
	}

	double nrt(double x, double y) {
		return pow(x, 1.0 / y);
	}

	double exp(double x) {
		return std::exp(x);
	}

	double ln(double x) {
		return std::log(x);
	}

	double lg(double x) {
		return std::log10(x);
	}

	double log2(double x) {
		return std::log2(x);
	}

	double log(double x, double y) {
		return ln(x) / ln(y);
	}

	double hypot(double x, double y) {
		return std::hypot(x, y);
	}

	double dtor(double deg) {
		return deg * PI / 180;
	}

	double rtod(double rad) {
		return rad * 180 / PI;
	}

	double sin(double x) {
		return std::sin(x);
	}

	double cos(double x) {
		return std::cos(x);
	}

	double tan(double x) {
		return std::tan(x);
	}

	double arcsin(double x) {
		return std::asin(x);
	}

	double arccos(double x) {
		return std::acos(x);
	}

	double arctan(double x) {
		return std::atan(x);
	}

	double arctan2(double y, double x) {
		return std::atan2(y, x);
	}

	double sinh(double x) {
		return std::sinh(x);
	}

	double cosh(double x) {
		return std::cosh(x);
	}

	double tanh(double x) {
		return std::tanh(x);
	}

	double arsinh(double x) {
		return std::asinh(x);
	}

	double arcosh(double x) {
		return std::acosh(x);
	}

	double artanh(double x) {
		return std::atanh(x);
	}
}