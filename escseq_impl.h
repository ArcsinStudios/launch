#pragma once

#include <iostream>
#include <string>

namespace launch {
	class escseq_manip {
	private:
		std::string seq;

	public:
		escseq_manip(std::string _seq) : seq(_seq) {}

		friend std::ostream& operator<<(std::ostream& out, const escseq_manip& manip);
	};

	inline const escseq_manip reset_cursor_pos("\033[H");
	inline const escseq_manip show_cursor("\033[?25h");
	inline const escseq_manip hide_cursor("\033[?25l");
	inline const escseq_manip clear("\033[J");
	inline const escseq_manip clear_front("\033[0J");
	inline const escseq_manip clear_back("\033[1J");
	inline const escseq_manip erase("\033[K");
	inline const escseq_manip erase_front("\033[0K");
	inline const escseq_manip erase_back("\033[1K");
	inline const escseq_manip bold("\033[1m");
	inline const escseq_manip dim("\033[2m");
	inline const escseq_manip italic("\033[3m");
	inline const escseq_manip underline("\033[4m");
	inline const escseq_manip blink("\033[5m");
	inline const escseq_manip inverse("\033[7m");
	inline const escseq_manip hidden("\033[8m");
	inline const escseq_manip strikethrough("\033[9m");
	inline const escseq_manip reset_font("\033[0m");
	inline const escseq_manip reset_foreground("\033[39m");
	inline const escseq_manip reset_background("\033[49m");

	escseq_manip cursor_goto(int line, int col);
	escseq_manip cursor_up(int count);
	escseq_manip cursor_down(int count);
	escseq_manip cursor_right(int count);
	escseq_manip cursor_left(int count);

	escseq_manip foreground_color(unsigned char r, unsigned char g, unsigned char b);
	escseq_manip background_color(unsigned char r, unsigned char g, unsigned char b);

	inline const unsigned char FONT_BOLD = 0b00000001;
	inline const unsigned char FONT_DIM = 0b00000010;
	inline const unsigned char FONT_ITALIC = 0b00000100;
	inline const unsigned char FONT_UNDERLINE = 0b00001000;
	inline const unsigned char FONT_BLINK = 0b00010000;
	inline const unsigned char FONT_INVERSE = 0b00100000;
	inline const unsigned char FONT_HIDDEN = 0b01000000;
	inline const unsigned char FONT_STRIKETHROUGH = 0b10000000;

	class font_manip {
	private:
		unsigned char flags;

	public:
		font_manip(unsigned char _flags) : flags(_flags) {}

		friend std::ostream& operator<<(std::ostream& out, const font_manip& manip);
	};

	font_manip gen_font(unsigned char flags);

	class launch_endl {
	private:
		bool fast = false;

	public:
		launch_endl(bool _fast) : fast(_fast) {}

		friend std::ostream& operator<<(std::ostream& out, const launch_endl& manip);
	};

	inline const launch_endl l_endl(false);
	inline const launch_endl l_endl_fast(true);
}