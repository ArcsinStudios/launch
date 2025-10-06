#include "launch.h"
#include <chrono>
#include <iostream>
#include <string>
using namespace launch;

class nullbuf : public std::streambuf {
public:
	int overflow(int c) override {
		return c;
	}
};

class nullstream : public std::ostream {
private:
	nullbuf buffer;

public:
	nullstream() : std::ostream(&buffer) {}
};

nullstream nullout;

long long benchmark_0(hedgehog& hh) {
	hh.clear();
	hh.puff(768);
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 256; ++i) {
		hh.stick(i);
		hh.stick((double)i);
		hh.stick(std::to_string(i));
	}
	std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

long long benchmark_1(hedgehog& hh) {
	benchmark_0(hh);
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
	for (const hedgehog_elemproxy& elem : hh) {
		nullout << elem;
	}
	std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

long long benchmark_2(hedgehog& hh) {
	hh.clear();
	hh.fill(0, 256);
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 256; ++i) {
		hh[i] += i;
	}
	std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main(int argc, char* argv[]) {
	hedgehog hh = {};
	std::cout << benchmark_0(hh) << '\n';
	std::cout << benchmark_1(hh) << '\n';
	std::cout << benchmark_2(hh) << '\n';
	return 0;
}