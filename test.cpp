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
	std::cout << "Benchmark 0, adding 768 elements: " << benchmark_0(hh) << " microseconds\n";
	std::cout << "Benchmark 1, printing 768 elements: " << benchmark_1(hh) << " microseconds\n";
	std::cout << "Benchmark 2, calculating 256 times: " << benchmark_2(hh) << " microseconds\n";
	std::cout
		<< gen_font(FONT_ITALIC | FONT_UNDERLINE)
		<< foreground_color(0, 0, 255)
		<< background_color(255, 255, 255)
		<< "Hyperlink\n"
		<< foreground_color(128, 0, 255)
		<< "Hyperlink (clicked)"
		<< l_endl_fast;
	std::cout
		<< foreground_color(198, 120, 221)
		<< "int "
		<< foreground_color(224, 108, 117)
		<< "var "
		<< foreground_color(97, 175, 239)
		<< "= "
		<< foreground_color(209, 154, 102)
		<< "42"
		<< foreground_color(97, 175, 239)
		<< "; "
		<< foreground_color(127, 132, 142)
		<< "// This is the palette of One Dark Pro"
		<< l_endl_fast;
	return 0;
}