#pragma once

#include <algorithm>
#include <cmath>
#include <numeric>

#include "goodmath_consts.h"

namespace launch {
	double abs(double x);

	double floor(double x);

	double ceil(double x);

	double round(double x);

	double trunc(double x);

	long long floor_ll(double x);

	long long ceil_ll(double x);

	long long round_ll(double x);

	long long trunc_ll(double x);

	double max(double x, double y);

	double min(double x, double y);

	double pow(double x, double y);

	double mod(double x, double y);

	long long gcd(long long x, long long y);

	long long lcm(long long x, long long y);

	double sqrt(double x);

	double cbrt(double x);

	double nrt(double x, double y);

	double exp(double x);

	double ln(double x);

	double lg(double x);

	double log2(double x);

	double log(double x, double y);

	double hypot(double x, double y);

	double dtor(double deg);

	double rtod(double rad);

	double sin(double x);

	double cos(double x);

	double tan(double x);

	double arcsin(double x);

	double arccos(double x);

	double arctan(double x);

	double arctan2(double y, double x);

	double sinh(double x);

	double cosh(double x);

	double tanh(double x);

	double arcsinh(double x);

	double arccosh(double x);

	double arctanh(double x);
}