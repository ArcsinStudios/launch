#define LAUNCH_FMTIO_NULLSTREAM
#define LAUNCH_GOODMATH_ARINT
#define LAUNCH_LIDEVEC
#define LAUNCH_NO_THREAD_SAFE
#include "launch.h"
#include <iostream>
#include <istream>
#include <random>
#include <string>
using namespace launch;

long long hedgehog_test0(hedgehog& hh) {
	stopwatch watch;
	hh.clear();
	hh.reserve_more(768);
	watch.start();
	for (int i = 0; i < 256; ++i) {
		hh.push_back(i);
		hh.push_back((double)i);
		hh.push_back(std::to_string(i));
	}
	watch.stop();
	return watch.get_duration().microseconds();
}

long long hedgehog_test1(hedgehog& hh) {
	hedgehog_test0(hh);
	stopwatch watch;
	watch.start();
	for (const hedgehog_elemproxy& elem : hh) {
		nullout << elem;
	}
	watch.stop();
	return watch.get_duration().microseconds();
}

long long hedgehog_test2(hedgehog& hh) {
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

void lidevec_test() {
	lidevec<int> lvec;
	std::vector<int> vec;
	stopwatch watch;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 1);
	watch.start();
	for (int i = 0; i < 100000; ++i) {
		vec.push_back(i);
	}
	watch.stop();
	std::cout << "std::vector took: " << watch.get_duration().microseconds() << " microseconds\n";
	watch.start();
	for (int i = 0; i < 100000; ++i) {
		lvec.push_back(i);
	}
	watch.stop();
	std::cout << "lidevec took: " << watch.get_duration().microseconds() << " microseconds\n";
	watch.start();
	for (int i = 0; i < 50000; ++i) {
		if (distrib(gen)) {
			vec.erase(vec.begin() + i);
		}
	}
	watch.stop();
	std::cout << "std::vector took: " << watch.get_duration().microseconds() << " microseconds\n";
	watch.start();
	for (int i = 0; i < 50000; ++i) {
		if (distrib(gen)) {
			lvec.erase(i);
		}
	}
	watch.stop();
	std::cout << "lidevec took: " << watch.get_duration().microseconds() << " microseconds\n";
}

int main(int argc, char* argv[]) {
	clap parser(argc, argv, {
		{"c", "caref"},
		{"e", "escseq"},
		{"h", "hedgehog"},
		{"m", "goodmath"},
		{"s", "goodstr"},
		{"l", "lidevec"}
	});
	if (parser.get_flag("caref")) {
		caref<int> observer;
		std::cout << "Outer scope: observer constructed\n";
		std::cout << "Outer scope: entering inner scope\n";
		{
			caref<int> owner(new int(42));
			std::cout << "Inner scope: owner constructed, value: " << *owner << '\n';
			observer = owner;
			std::cout << "Inner scope: observing owner, value: " << *observer << '\n';
			owner.move(observer);
			std::cout << "Inner scope: moving ownership to observer\n";
			std::cout << "Inner scope: exiting inner scope\n";
		}
		std::cout << "Outer scope: owner destructed\n";
		std::cout << "Outer scope: value held by observer: " << *observer << '\n';
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
	else if (parser.get_flag("hedgehog")) {
		hedgehog hh = {};
		std::cout << "Benchmark 0, adding 768 elements: " << hedgehog_test0(hh) << " microseconds\n";
		std::cout << "Benchmark 1, printing 768 elements: " << hedgehog_test1(hh) << " microseconds\n";
		std::cout << "Benchmark 2, calculating 256 times: " << hedgehog_test2(hh) << " microseconds\n";
	}
	else if (parser.get_flag("goodmath")) {
		long long _num, digit;
		std::cout << "Enter two numbers please: ";
		std::cin >> _num >> digit;
		arint num = _num;
		std::cout << "Digit " << digit << " of " << _num << " is " << (long long)(num[digit - 1]) << ".\n";
	}
	else if (parser.get_flag("goodstr")) {
		hstr str0, str1, str2;
		std::cout << "Enter three strings:\n";
		std::getline(std::cin >> std::ws, str0.raw());
		std::getline(std::cin >> std::ws, str1.raw());
		std::getline(std::cin >> std::ws, str2.raw());
		std::cout << "After replacing \"" << str1 << "\" with \"" << str2 << "\": " << replace(str0, str1, str2) << '\n';
	}
	else if (parser.get_flag("lidevec")) {
		lidevec_test();
	}
	else {
		std::cout << "Error: no test programs match with the argument(s) given.\n";
	}
	return 0;
}