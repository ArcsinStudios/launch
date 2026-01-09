#include <list>
#include <vector>

#include "launch.h"
using namespace launch;
using namespace launch::leisure;

long long hedgehog_test0(hedgehog& hh) {
	stopwatch watch;
	hh.clear();
	hh.reserve(768);
	watch.start();
	for (int i = 0; i < 256; ++i) {
		hh.push_back(i);
		hh.push_back((double)i);
		hh.push_back(std::to_string(i));
	}
	watch.stop();
	return watch.get_dur().microseconds();
}

long long hedgehog_test1(hedgehog& hh) {
	hedgehog_test0(hh);
	stopwatch watch;
	std::string fmt = "";
	int size = hh.size();
	for (int i = 0; i < size; ++i) {
		fmt += "{" + std::to_string(i) + "} ";
	}
	watch.start();
	fmtout(fmt, hh, nullout);
	watch.stop();
	return watch.get_dur().microseconds();
}

long long hedgehog_test2(hedgehog& hh) {
	stopwatch watch;
	hh.clear();
	for (int i = 0; i < 256; ++i) {
		hh.push_back(0);
	}
	watch.start();
	for (int i = 0; i < 256; ++i) {
		hh[i] += i;
	}
	watch.stop();
	return watch.get_dur().microseconds();
}

void hedgehog_test3() {
	hedgehog hh = { 42, 3.14, "Hello World!" };
	fmtout("int: {0}, double: {1}, const char*: {2}\n", hh);
	for (hedgehog_elemproxy& elem : hh) {
		try {
			elem += 1;
		}
		catch (const std::runtime_error& e) {
			fmtout("Oops: {0}\n", { e.what() });
		}
	}
	hh[2] += " Hello Everyone!";
	fmtout("int: {0}, double: {1}, std::string: {2}\n", hh);
}

template <typename T>
long long lidevec_test0() {
	T container;
	stopwatch watch;
	watch.start();
	for (int i = 0; i < 100000; ++i) {
		container.push_back(i);
	}
	watch.stop();
	return watch.get_dur().microseconds();
}

template <typename T>
long long lidevec_test0(T& container) {
	stopwatch watch;
	watch.start();
	for (int i = 0; i < 100000; ++i) {
		container.push_back(i);
	}
	watch.stop();
	return watch.get_dur().microseconds();
}

template <typename T>
long long lidevec_test1() {
	T container;
	lidevec_test0<T>(container);
	stopwatch watch;
	randgen_int rand(0, 1);
	watch.start();
	watch.pause();
	for (int i = 0; i < 50000; ++i) {
		if (i >= container.size()) {
			continue;
		}
		typename T::iterator it = container.begin();
		for (int j = 0; j < i; ++j) {
			++it;
		}
		if (rand.next()) {
			watch.resume();
			container.erase(it);
			watch.pause();
		}
	}
	watch.resume();
	watch.stop();
	return watch.get_dur().microseconds();
}

template <>
long long lidevec_test1<lidevec<int>>() {
	lidevec<int> container;
	lidevec_test0(container);
	stopwatch watch;
	randgen_int rand(0, 1);
	watch.start();
	for (int i = 0; i < 50000; ++i) {
		if (rand.next()) {
			container.erase(i);
		}
	}
	watch.stop();
	return watch.get_dur().microseconds();
}

template <typename T>
long long lidevec_test2() {
	T container;
	lidevec_test0<T>(container);
	stopwatch watch;
	randgen_int rand(0, 1);
	watch.start();
	watch.pause();
	for (int i = 0; i < 50000; ++i) {
		if (i >= container.size()) {
			continue;
		}
		typename T::iterator it = container.begin();
		for (int j = 0; j < i; ++j) {
			++it;
		}
		if (rand.next()) {
			watch.resume();
			container.insert(it, i);
			watch.pause();
		}
	}
	watch.resume();
	watch.stop();
	return watch.get_dur().microseconds();
}

template <>
long long lidevec_test2<lidevec<int>>() {
	lidevec<int> container;
	lidevec_test0(container);
	stopwatch watch;
	randgen_int rand(0, 1);
	watch.start();
	for (int i = 0; i < 50000; ++i) {
		if (rand.next()) {
			container.insert(i, i);
		}
	}
	watch.stop();
	return watch.get_dur().microseconds();
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
	int cnt = 0;
	fmtout("=== START OF PROGRAM ===\n");
	if (parser.get_flag("caref")) {
		++cnt;
		fmtout("=== START OF TEST - CAREF ===\n");
		caref<int> observer;
		fmtout("Outer scope: observer constructed\n");
		fmtout("Outer scope: entering inner scope\n");
		{
			caref<int> owner(new int(42));
			fmtout("Inner scope: owner constructed, value: {0}\n", { *owner });
			observer = owner;
			fmtout("Inner scope: observing owner, value: {0}\n", { *observer });
			owner.move(observer);
			fmtout("Inner scope: moving ownership to observer\n");
			fmtout("Inner scope: exiting inner scope\n");
		}
		fmtout("Outer scope: owner destructed\n");
		fmtout("Outer scope: value held by observer: {0}\n", { *observer });
		fmtout("=== END OF TEST - CAREF ===\n");
	}
	if (parser.get_flag("escseq")) {
		++cnt;
		fmtout("=== START OF TEST - ESCSEQ ===\n");
		fmtout("{0}{1}{2}Hyperlink\n", {
			gen_style(escseq_style::italic | escseq_style::underline),
			foreground_color(0, 0, 255),
			background_color(255, 255, 255)
		});
		fmtout("{0}Hyperlink (clicked){1}", {
			foreground_color(128, 0, 255),
			rendl_fast
		});
		fmtout("{0}int {1}var {2}= {3}42{2}; {4}// This is the palette of One Dark Pro{5}", {
			foreground_color(198, 120, 221),
			foreground_color(224, 108, 117),
			foreground_color(97, 175, 239),
			foreground_color(209, 154, 102),
			foreground_color(127, 132, 142),
			rendl_fast
		});
		fmtout("=== END OF TEST - ESCSEQ ===\n");
	}
	if (parser.get_flag("hedgehog")) {
		++cnt;
		fmtout("=== START OF TEST - HEDGEHOG ===\n");
		hedgehog hh = {};
		fmtout("Benchmark 0, adding 768 elements: {0} microseconds\n", { hedgehog_test0(hh) });
		fmtout("Benchmark 1, printing 768 elements: {0} microseconds\n", { hedgehog_test1(hh) });
		fmtout("Benchmark 2, calculating 256 times: {0} microseconds\n", { hedgehog_test2(hh) });
		fmtout("Test 3:\n");
		hedgehog_test3();
		fmtout("=== END OF TEST -  ===\n");
	}
	if (parser.get_flag("goodmath")) {
		++cnt;
		fmtout("=== START OF TEST - GOODMATH ===\n");
		hedgehog hh;
		arreal lhs, rhs;
		char op;
		fmtout("Enter a math expression please (e.g. 1 + 2, -1/2 * 3/4): ");
		fmtin<arreal, char, arreal>(hh);
		lhs = hh[0].as<arreal>();
		op = hh[1].as<char>();
		rhs = hh[2].as<arreal>();
		fmtout("{0} {1} {2} = ", { lhs, op, rhs });
		switch (op) {
		case '+':
			fmtout("{0}", { lhs + rhs });
			break;
		case '-':
			fmtout("{0}", { lhs - rhs });
			break;
		case '*':
			fmtout("{0}", { lhs * rhs });
			break;
		case '/':
			fmtout("{0}", { lhs / rhs });
			break;
		default:
			fmtout("Wrong operator!");
		}
		fmtout("\n");
		fmtout("=== END OF TEST - GOODMATH ===\n");
	}
	if (parser.get_flag("goodstr")) {
		++cnt;
		fmtout("=== START OF TEST - GOODSTR ===\n");
		std::string str0, str1, str2;
		fmtout("Enter three strings:\n");
		std::getline(std::cin >> std::ws, str0);
		std::getline(std::cin >> std::ws, str1);
		std::getline(std::cin >> std::ws, str2);
		fmtout("After replacing \"{0}\" with \"{1}\": {2}\n", { str1, str2, replace(str0, str1, str2) });
		fmtout("=== END OF TEST - GOODSTR ===\n");
	}
	if (parser.get_flag("lidevec")) {
		fmtout("INFO: PLEASE WAIT PATIENTLY WHILE THE TEST IS RUNNING.\n");
		fmtout("      THIS IS ABOUT TO TAKE 1-2 MINUTES.\n");
		fmtout("      PRESS ENTER TO PROCEED.");
		std::cin.get();
		++cnt;
		fmtout("=== START OF TEST - LIDEVEC ===\n");
		fmtout("Pushing back 100,000 times.\n");
		fmtout("std::list took: {0} microseconds\n", { lidevec_test0<std::list<int>>() });
		fmtout("std::vector took: {0} microseconds\n", { lidevec_test0<std::vector<int>>() });
		fmtout("lidevec took: {0} microseconds\n", { lidevec_test0<lidevec<int>>() });
		fmtout("Erasing ~25,000 times.\n");
		fmtout("std::list took: {0} microseconds\n", { lidevec_test1<std::list<int>>() });
		fmtout("std::vector took: {0} microseconds\n", { lidevec_test1<std::vector<int>>() });
		fmtout("lidevec took: {0} microseconds\n", { lidevec_test1<lidevec<int>>() });
		fmtout("Inserting ~25,000 times.\n");
		fmtout("std::list took: {0} microseconds\n", { lidevec_test2<std::list<int>>() });
		fmtout("std::vector took: {0} microseconds\n", { lidevec_test2<std::vector<int>>() });
		fmtout("lidevec took: {0} microseconds\n", { lidevec_test2<lidevec<int>>() });
		fmtout("=== END OF TEST - LIDEVEC ===\n");
	}
	fmtout("=== END OF PROGRAM - {0} TEST(S) EXECUTED ===\n", { cnt });
	return 0;
}