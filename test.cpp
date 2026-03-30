#include <fstream>

#include "include/launch.h"
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
	hedgehog cont;
	for (int i = 0; i < 256; ++i) {
		cont.push_back(i);
		cont.push_back(i / 10.0);
		cont.push_back(i % 2 == 0);
		cont.push_back(std::to_string(i));
	}
	size_t hh_size = cont.size();
	std::string fmt = "[ ]";
	stopwatch watch;
	watch.start();
	fmtout(fmt, cont, false, nullout);
	watch.stop();
	return watch.get_dur().microseconds();
}

long long hedgehog_test2() {
	hedgehog cont;
	for (int i = 0; i < 256; ++i) {
		cont.push_back(0);
		cont.push_back(0ll);
		cont.push_back(0.0f);
		cont.push_back(0.0);
	}
	size_t hh_size = cont.size();
	stopwatch watch;
	watch.start();
	for (int i = 0; i < hh_size; ++i) {
		cont[i] += i / 4;
	}
	watch.stop();
	return watch.get_dur().microseconds();
}

void hedgehog_test3() {
	hedgehog cont = { 42, 3.14, std::string("Hello World!") };
	fmtout("int: {}, double: {}, std::string: {}\n", cont);
	for (hedgehog_elemproxy& elem : cont) {
		try {
			elem += 1;
		}
		catch (const std::runtime_error& e) {
			fmtout("Oops: {0}\n", { e.what() });
		}
	}
	fmtout("int: {}, double: {}, std::string: {}\n", cont);
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
		std::cout << std::boolalpha;
		std::cin >> std::boolalpha;
		std::ifstream file("splashes.txt");
		std::vector<std::string> splashes;
		if (file.is_open()) {
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
		fmtout("[]\n", {
			artwork,
			foreground_color(255, 255, 0),
			cursor_left(65),
			VERSION,
			cursor_right(65 - std::strlen(VERSION) - splashes[splash_index].length()),
			splashes[splash_index],
			rendl_fast
		});
		size_t cnt = 0;
		fmtout("=== START OF PROGRAM ===\n");
		if (parser.get_flag("escseq") || parser.get_flag("all")) {
			++cnt;
			fmtout("=== START OF TEST - ESCSEQ ===\n");
			fmtout("[]Hyperlink\n", {
				gen_style(escseq_style::italic | escseq_style::underline),
				foreground_color(0, 0, 255),
				background_color(255, 255, 255)
			});
			fmtout("[Hyperlink (clicked)]", {
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
			fmtout("Test 1, printing 1024 elements: {}us\n", { hedgehog_test1() });
			fmtout("Test 2, calculating 1024 times: {}us\n", { hedgehog_test2() });
			fmtout("Test 3:\n");
			hedgehog_test3();
			fmtout("=== END OF TEST - HEDGEHOG ===\n");
		}
		if (parser.get_flag("goodmath") || parser.get_flag("all")) {
			++cnt;
			fmtout("=== START OF TEST - GOODMATH ===\n");
			double deg;
			fmtout("Enter an angle (in degrees) please: ");
			fmtin_single(deg);
			double rad = dtor(deg);
			double cos_ = ::launch::cos(rad);
			double sin_ = ::launch::sin(rad);
			fmtout(
				"If O is at (0, 0), A is at (1, 0), both OA and OP are 1, "
				"and angle AOP is {} degrees, then P is at ({}, {}).\n"
				"By the way, this should be 1: {}.\n",
				{ deg, cos_, sin_, ::launch::pow(cos_, 2) + ::launch::pow(sin_, 2) }
			);
			fmtout("=== END OF TEST - GOODMATH ===\n");
		}
		if (parser.get_flag("goodstr") || parser.get_flag("all")) {
			++cnt;
			fmtout("=== START OF TEST - GOODSTR ===\n");
			std::string str0, str1, str2;
			fmtout("Enter three strings:\n");
			fmtin_line(str0);
			fmtin_line(str1);
			fmtin_line(str2);
			fmtout(
				"After replacing \"{}\"s in \"{}\" with \"{}\": {}\n",
				{ str1, str0, str2, replace(str0, str1, str2) }
			);
			fmtout("=== END OF TEST - GOODSTR ===\n");
		}
		if (parser.get_flag("arithing") || parser.get_flag("all")) {
			++cnt;
			fmtout("=== START OF TEST - ARITHING ===\n");
			hedgehog cont;
			arreal lhs, rhs, res;
			char op;
			fmtout("Enter a math expression please (e.g. 1 + 2, -1/2 * 3/4): ");
			fmtin<arreal, char, arreal>(cont);
			lhs = cont[0].as<arreal>();
			op = cont[1].as<char>();
			rhs = cont[2].as<arreal>();
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
			if (denominator(res) == 1) {
				fmtout("{} {} {} = {}\n", { lhs, op, rhs, res });
			}
			else {
				fmtout("{} {} {} = {} = {}\n", { lhs, op, rhs, res, to_decimal(res) });
			}
			fmtout("=== END OF TEST - ARITHING ===\n");
		}
		if (parser.get_flag("exfmtio") || parser.get_flag("all")) {
			++cnt;
			fmtout("=== START OF TEST - EXFMTIO ===\n");
			size_t cnt;
			hedgehog cont;
			std::string fmt = "----------------------------------------\nYou entered:\n";
			fmtout("How many elements you're about to enter? ");
			fmtin_single(cnt);
			fmtout("----------------------------------------\nPlese enter {} element(s):\n", { cnt });
			fmtin_deduce_auto(cont, cnt);
			size_t hh_size = cont.size();
			for (size_t i = 0; i < hh_size; ++i) {
				fmt = fmt + "{" + std::to_string(i) + "}: {" + std::to_string(i + hh_size) + "}\n";
				cont.push_back(cont[i].type().name());
			}
			fmtout(fmt, cont);
			fmtout("=== END OF TEST - EXFMTIO ===\n");
		}
		fmtout("=== END OF PROGRAM - {} TEST(S) EXECUTED ===\n", { cnt });
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