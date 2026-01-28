#include <list>
#include <vector>

#include "launch.h"
using namespace launch;
using namespace leisure;

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

int main(int argc, char* argv[]) {
	clap parser(argc, argv, {
		{"e", "escseq"},
		{"h", "hedgehog"},
		{"m", "goodmath"},
		{"s", "goodstr"},
		{"a", "arithing"},
		{"f", "exfmtio"}
	});
	int cnt = 0;
	fmtout("=== START OF PROGRAM ===\n");
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
		fmtout("Enter an angle (in degrees) please: ");
		fmtin<double>(hh);
		double rad = dtor(hh[0].as<double>());
		double cos_ = ::launch::cos(rad);
		double sin_ = ::launch::sin(rad);
		fmtout(
			"If O is at (0, 0), A is at (1, 0), both OA and OP are 1, "
			"and angle AOP is {0} degrees, then P is at ({1}, {2}).\n"
			"By the way, this should be 1: {3}.\n",
			{ hh[0], cos_, sin_, ::launch::pow(cos_, 2) + ::launch::pow(sin_, 2) }
		);
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
	if (parser.get_flag("arithing")) {
		++cnt;
		fmtout("=== START OF TEST - ARITHING ===\n");
		hedgehog hh;
		arreal lhs, rhs, res;
		char op;
		fmtout("Enter a math expression please (e.g. 1 + 2, -1/2 * 3/4): ");
		fmtin<arreal, char, arreal>(hh);
		lhs = hh[0].as<arreal>();
		op = hh[1].as<char>();
		rhs = hh[2].as<arreal>();
		switch (op) {
		case '+':
			res = lhs + rhs;
			break;
		case '-':
			res = lhs - rhs;
			break;
		case '*':
			res = lhs * rhs;
			break;
		case '/':
			res = lhs / rhs;
			break;
		case '%':
			res = lhs % rhs;
			break;
		default:
			res = arint(0, arint_specval::nan);
		}
		fmtout("{0} {1} {2} = {3} = {4}\n", { lhs, op, rhs, res, res.to_decimal() });
		fmtout("=== END OF TEST - ARITHING ===\n");
	}
	if (parser.get_flag("exfmtio")) {
		++cnt;
		fmtout("=== START OF TEST - EXFMTIO ===\n");
		hedgehog hh = { -1, -1 };
		fmtout("Enter anything: ");
		fmtin_deduce_auto(hh[0]);
		hh[1] = hh[0].type().name();
		fmtout("Got {0} with type {1}\n", hh);
		fmtout("=== END OF TEST - EXFMTIO ===\n");
	}
	fmtout("=== END OF PROGRAM - {0} TEST(S) EXECUTED ===\n", { cnt });
	return 0;
}