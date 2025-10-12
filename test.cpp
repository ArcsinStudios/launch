#include "launch.h"
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
	stopwatch watch;
	hh.clear();
	hh.puff(768);
	watch.start();
	for (int i = 0; i < 256; ++i) {
		hh.stick(i);
		hh.stick((double)i);
		hh.stick(std::to_string(i));
	}
	watch.stop();
	return watch.get_duration().microseconds();
}

long long benchmark_1(hedgehog& hh) {
	benchmark_0(hh);
	stopwatch watch;
	watch.start();
	for (const hedgehog_elemproxy& elem : hh) {
		nullout << elem;
	}
	watch.stop();
	return watch.get_duration().microseconds();
}

long long benchmark_2(hedgehog& hh) {
	stopwatch watch;
	hh.clear();
	hh.fill(0, 256);
	watch.start();
	for (int i = 0; i < 256; ++i) {
		hh[i] += i;
	}
	watch.stop();
	return watch.get_duration().microseconds();
}

int main(int argc, char* argv[]) {
	clap parser(argc, argv, {{"h", "hedgehog"}, {"e", "escseq"}});
	if (parser.get_flag("hedgehog")) {
		hedgehog hh = {};
		std::cout << "Benchmark 0, adding 768 elements: " << benchmark_0(hh) << " microseconds\n";
		std::cout << "Benchmark 1, printing 768 elements: " << benchmark_1(hh) << " microseconds\n";
		std::cout << "Benchmark 2, calculating 256 times: " << benchmark_2(hh) << " microseconds\n";
	}
	else if (parser.get_flag("escseq")) {
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
	}
	else {
		std::cout << "Error: no test programs match with the argument(s) given.\n";
	}
	return 0;
}