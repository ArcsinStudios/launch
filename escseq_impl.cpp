#include "escseq_impl.h"

namespace launch {
	std::ostream& operator<<(std::ostream& out, const escseq_manip& manip) {
		return out << manip.seq;
	}

	escseq_manip cursor_goto(int line, int col) {
		return escseq_manip("\033[" + std::to_string(line) + ";" + std::to_string(col) + "H");
	}
	escseq_manip cursor_up(int count) {
		return escseq_manip("\033[" + std::to_string(count) + "A");
	}
	escseq_manip cursor_down(int count) {
		return escseq_manip("\033[" + std::to_string(count) + "B");
	}
	escseq_manip cursor_right(int count) {
		return escseq_manip("\033[" + std::to_string(count) + "C");
	}
	escseq_manip cursor_left(int count) {
		return escseq_manip("\033[" + std::to_string(count) + "D");
	}

	escseq_manip foreground_color(unsigned char r, unsigned char g, unsigned char b) {
		return escseq_manip("\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m");
	}
	escseq_manip background_color(unsigned char r, unsigned char g, unsigned char b) {
		return escseq_manip("\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m");
	}

	std::ostream& operator<<(std::ostream& out, const font_manip& manip) {
		unsigned char _flags = manip.flags;
		if (_flags & FONT_BOLD) {
			out << bold;
		}
		if (_flags & FONT_DIM) {
			out << dim;
		}
		if (_flags & FONT_ITALIC) {
			out << italic;
		}
		if (_flags & FONT_UNDERLINE) {
			out << underline;
		}
		if (_flags & FONT_BLINK) {
			out << blink;
		}
		if (_flags & FONT_INVERSE) {
			out << inverse;
		}
		if (_flags & FONT_HIDDEN) {
			out << hidden;
		}
		if (_flags & FONT_STRIKETHROUGH) {
			out << strikethrough;
		}
		return out;
	}

	font_manip gen_font(unsigned char flags) {
		return font_manip(flags);
	}

	std::ostream& operator<<(std::ostream& out, const launch_endl& manip) {
		if (manip.fast) {
			out << '\n';
		}
		else {
			out << std::endl;
		}
		return out << reset_font;
	}
}