#pragma once

#include <iostream>
#include <string>
#include <type_traits>

namespace launch {
	class escseq_manip {
	private:
		std::string seq;

	public:
		escseq_manip(std::string _seq) : seq(_seq) {}

		friend std::ostream& operator<<(std::ostream& out, const escseq_manip& manip);
	};

	inline const escseq_manip reset_cursor("\033[H");
	inline const escseq_manip show_cursor("\033[?25h");
	inline const escseq_manip hide_cursor("\033[?25l");
	inline const escseq_manip clear_front("\033[0J");
	inline const escseq_manip clear_back("\033[1J");
	inline const escseq_manip clear_screen("\033[2J");
	inline const escseq_manip erase_front("\033[0K");
	inline const escseq_manip erase_back("\033[1K");
	inline const escseq_manip erase_line("\033[2K");
	inline const escseq_manip bold("\033[1m");
	inline const escseq_manip dim("\033[2m");
	inline const escseq_manip italic("\033[3m");
	inline const escseq_manip underline("\033[4m");
	inline const escseq_manip blink("\033[5m");
	inline const escseq_manip inverse("\033[7m");
	inline const escseq_manip hidden("\033[8m");
	inline const escseq_manip strikethrough("\033[9m");
	inline const escseq_manip reset_foreground("\033[39m");
	inline const escseq_manip reset_background("\033[49m");
	inline const escseq_manip reset_font("\033[0m");

	escseq_manip cursor_goto(int line, int col);
	escseq_manip cursor_up(int count);
	escseq_manip cursor_down(int count);
	escseq_manip cursor_right(int count);
	escseq_manip cursor_left(int count);

	escseq_manip foreground_color(unsigned char r, unsigned char g, unsigned char b);
	escseq_manip background_color(unsigned char r, unsigned char g, unsigned char b);

	enum class escseq_style : unsigned char {
		bold = 0b00000001,
		dim = 0b00000010,
		italic = 0b00000100,
		underline = 0b00001000,
		blink = 0b00010000,
		inverse = 0b00100000,
		hidden = 0b01000000,
		strikethrough = 0b10000000
	};

	escseq_style operator|(escseq_style lhs, escseq_style rhs);
	escseq_style operator&(escseq_style lhs, escseq_style rhs);

	class style_manip {
	private:
		escseq_style flags;

	public:
		style_manip(escseq_style _flags) : flags(_flags) {}

		friend std::ostream& operator<<(std::ostream& out, const style_manip& manip);
	};

	style_manip gen_style(escseq_style flags);

	class reset_endl {
	private:
		bool fast = false;

	public:
		reset_endl(bool _fast) : fast(_fast) {}

		friend std::ostream& operator<<(std::ostream& out, const reset_endl& manip);
	};

	inline const reset_endl rendl(false);
	inline const reset_endl rendl_fast(true);
}