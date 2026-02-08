#include "launch_config.h"

#include "escseq_impl.h"

namespace launch {
	std::ostream& operator<<(std::ostream& out, const escseq_manip& manip) {
		return out << manip.seq;
	}

	escseq_manip cursor_goto(size_t line, size_t col) {
		return escseq_manip("\033[" + std::to_string(line) + ";" + std::to_string(col) + "H");
	}
	escseq_manip cursor_up(size_t count) {
		return escseq_manip("\033[" + std::to_string(count) + "A");
	}
	escseq_manip cursor_down(size_t count) {
		return escseq_manip("\033[" + std::to_string(count) + "B");
	}
	escseq_manip cursor_right(size_t count) {
		return escseq_manip("\033[" + std::to_string(count) + "C");
	}
	escseq_manip cursor_left(size_t count) {
		return escseq_manip("\033[" + std::to_string(count) + "D");
	}

	escseq_manip foreground_color(unsigned char r, unsigned char g, unsigned char b) {
		return escseq_manip("\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m");
	}
	escseq_manip background_color(unsigned char r, unsigned char g, unsigned char b) {
		return escseq_manip("\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m");
	}

	escseq_style operator|(escseq_style lhs, escseq_style rhs) {
		return static_cast<escseq_style>(
			static_cast<std::underlying_type_t<escseq_style>>(lhs) |
			static_cast<std::underlying_type_t<escseq_style>>(rhs)
		);
	}

	escseq_style operator&(escseq_style lhs, escseq_style rhs) {
		return static_cast<escseq_style>(
			static_cast<std::underlying_type_t<escseq_style>>(lhs) &
			static_cast<std::underlying_type_t<escseq_style>>(rhs)
		);
	}

	std::ostream& operator<<(std::ostream& out, const style_manip& manip) {
		escseq_style _flags = manip.flags;
		if (static_cast<bool>(_flags & escseq_style::bold)) {
			out << bold;
		}
		if (static_cast<bool>(_flags & escseq_style::dim)) {
			out << dim;
		}
		if (static_cast<bool>(_flags & escseq_style::italic)) {
			out << italic;
		}
		if (static_cast<bool>(_flags & escseq_style::underline)) {
			out << underline;
		}
		if (static_cast<bool>(_flags & escseq_style::blink)) {
			out << blink;
		}
		if (static_cast<bool>(_flags & escseq_style::inverse)) {
			out << inverse;
		}
		if (static_cast<bool>(_flags & escseq_style::hidden)) {
			out << hidden;
		}
		if (static_cast<bool>(_flags & escseq_style::strikethrough)) {
			out << strikethrough;
		}
		return out;
	}

	style_manip gen_style(escseq_style flags) {
		return style_manip(flags);
	}

	std::ostream& operator<<(std::ostream& out, const reset_endl& manip) {
		if (manip.fast) {
			out << '\n';
		}
		else {
			out << std::endl;
		}
		return out << reset_font;
	}
}