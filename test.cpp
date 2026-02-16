#include <fstream>

#include "launch.h"
using namespace launch;
using namespace leisure;

const char* artwork =
R"( ___       ________  ___  ___  ________   ________  ___  ___     )""\n"
R"(|\  \     |\   __  \|\  \|\  \|\   ___  \|\   ____\|\  \|\  \    )""\n"
R"(\ \  \    \ \  \|\  \ \  \\\  \ \  \\ \  \ \  \___|\ \  \\\  \   )""\n"
R"( \ \  \    \ \   __  \ \  \\\  \ \  \\ \  \ \  \    \ \   __  \  )""\n"
R"(  \ \  \____\ \  \ \  \ \  \\\  \ \  \\ \  \ \  \____\ \  \ \  \ )""\n"
R"(   \ \_______\ \__\ \__\ \_______\ \__\\ \__\ \_______\ \__\ \__\)""\n"
R"(    \|_______|\|__|\|__|\|_______|\|__| \|__|\|_______|\|__|\|__|)";

long long hedgehog_test1() {
	hedgehog hh;
	for (int i = 0; i < 256; ++i) {
		hh.push_back(i);
		hh.push_back(i / 10.0);
		hh.push_back(i % 2 == 0);
		hh.push_back(std::to_string(i));
	}
	size_t size = hh.size();
	std::string fmt = "";
	for (int i = 0; i < size; ++i) {
		fmt += "{" + std::to_string(i) + "} ";
	}
	stopwatch watch;
	watch.start();
	fmtout(fmt, hh, nullout);
	watch.stop();
	return watch.get_dur().microseconds();
}

long long hedgehog_test2() {
	hedgehog hh;
	for (int i = 0; i < 256; ++i) {
		hh.push_back(0);
	}
	stopwatch watch;
	watch.start();
	for (int i = 0; i < 256; ++i) {
		hh[i] += i;
	}
	watch.stop();
	return watch.get_dur().microseconds();
}

void hedgehog_test3() {
	hedgehog hh = { 42, 3.14, std::string("Hello World!") };
	fmtout("int: {0}, double: {1}, std::string: {2}\n", hh);
	for (hedgehog_elemproxy& elem : hh) {
		try {
			elem += 1;
		}
		catch (const std::runtime_error& e) {
			fmtout("Oops: {0}\n", { e.what() });
		}
	}
	hh[2] += std::string(" Hello Everyone!");
	fmtout("int: {0}, double: {1}, std::string: {2}\n", hh);
}

int main(int argc, char* argv[]) {
	try {
		clap parser(argc, argv, {
			{"e", "escseq"},
			{"h", "hedgehog"},
			{"m", "goodmath"},
			{"s", "goodstr"},
			{"a", "arithing"},
			{"f", "exfmtio"}
		});
		fmtout(artwork);
		std::ifstream file("splashes.txt");
		std::vector<std::string> splashes;
		if (!file.is_open()) {
			splashes.push_back("Unable to load splashes!");
		}
		else {
			std::string line;
			while (std::getline(file, line)) {
				splashes.push_back(line);
			}
		}
		file.close();
		if (!splashes.size()) {
			splashes.push_back("Unable to load splashes!");
		}
		randgen_int<size_t> rand(0, splashes.size() - 1);
		size_t splash_index = rand.next();
		fmtout("{0}{1}{2}{3}\n", {
			cursor_left(splashes[splash_index].length()),
			foreground_color(255, 255, 0),
			splashes[splash_index],
			rendl_fast
		});
		size_t cnt = 0;
		fmtout("=== START OF PROGRAM ===\n");
		if (parser.get_flag("escseq") || parser.get_flag("all")) {
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
		if (parser.get_flag("hedgehog") || parser.get_flag("all")) {
			++cnt;
			fmtout("=== START OF TEST - HEDGEHOG ===\n");
			fmtout("Test 1, printing 1024 elements: {0} microseconds\n", { hedgehog_test1() });
			fmtout("Test 2, calculating 256 times: {0} microseconds\n", { hedgehog_test2() });
			fmtout("Test 3:\n");
			hedgehog_test3();
			fmtout("=== END OF TEST - HEDGEHOG ===\n");
		}
		if (parser.get_flag("goodmath") || parser.get_flag("all")) {
			++cnt;
			fmtout("=== START OF TEST - GOODMATH ===\n");
			hedgehog hh;
			fmtout("Enter an angle (in degrees) please: ");
			fmtin<double>(hh);
			double rad = dtor(hh[0].as<double>());
			double cos_ = ::launch::cos(rad);
			double sin_ = ::launch::sin(rad);
			hh.push_back(cos_);
			hh.push_back(sin_);
			hh.push_back(::launch::pow(cos_, 2) + ::launch::pow(sin_, 2));
			fmtout(
				"If O is at (0, 0), A is at (1, 0), both OA and OP are 1, "
				"and angle AOP is {0} degrees, then P is at ({1}, {2}).\n"
				"By the way, this should be 1: {3}.\n", hh
			);
			fmtout("=== END OF TEST - GOODMATH ===\n");
		}
		if (parser.get_flag("goodstr") || parser.get_flag("all")) {
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
		if (parser.get_flag("arithing") || parser.get_flag("all")) {
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
		if (parser.get_flag("exfmtio") || parser.get_flag("all")) {
			++cnt;
			fmtout("=== START OF TEST - EXFMTIO ===\n");
			hedgehog hh;
			fmtout("Enter anything: ");
			fmtin_deduce_auto(hh);
			hh.push_back(hh[0].type().name());
			fmtout("Got {0} with type {1}\n", hh);
			fmtout("=== END OF TEST - EXFMTIO ===\n");
		}
		fmtout("=== END OF PROGRAM - {0} TEST(S) EXECUTED ===\n", { cnt });
		if (!cnt) {
			fmtout(
				"\nOh, it seems like that none of our wonderful tests have been executed!\n"
				"Please consider running this program with one or more options.\n"
				"The available options are:\n"
				"--escseq (-e)\n"
				"--hedgehog (-h)\n"
				"--goodmath (-m)\n"
				"--goodstr (-s)\n"
				"--arithing (-a)\n"
				"--exfmtio (-f)\n"
				"--all\n"
			);
		}
	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << "\n";
		std::cerr << "Program exited abnormally.\n";
	}
	return 0;
}