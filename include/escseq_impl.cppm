export module escseq:impl;

import std;

namespace launch {
	export class escseq_manip {
	private:
		std::string seq;

	public:
		explicit escseq_manip(std::string _seq) : seq(_seq) {}

		friend std::ostream& operator<<(std::ostream& out, const escseq_manip& manip);
	};

	export const escseq_manip reset_cursor("\033[H");
	export const escseq_manip show_cursor("\033[?25h");
	export const escseq_manip hide_cursor("\033[?25l");
	export const escseq_manip clear_front("\033[0J");
	export const escseq_manip clear_back("\033[1J");
	export const escseq_manip clear_screen("\033[2J");
	export const escseq_manip erase_front("\033[0K");
	export const escseq_manip erase_back("\033[1K");
	export const escseq_manip erase_line("\033[2K");
	export const escseq_manip bold("\033[1m");
	export const escseq_manip dim("\033[2m");
	export const escseq_manip italic("\033[3m");
	export const escseq_manip underline("\033[4m");
	export const escseq_manip blink("\033[5m");
	export const escseq_manip inverse("\033[7m");
	export const escseq_manip hidden("\033[8m");
	export const escseq_manip strikethrough("\033[9m");
	export const escseq_manip reset_foreground("\033[39m");
	export const escseq_manip reset_background("\033[49m");
	export const escseq_manip reset_font("\033[0m");

	export escseq_manip cursor_goto(size_t line, size_t col);
	export escseq_manip cursor_up(size_t count);
	export escseq_manip cursor_down(size_t count);
	export escseq_manip cursor_right(size_t count);
	export escseq_manip cursor_left(size_t count);

	export escseq_manip foreground_color(unsigned char r, unsigned char g, unsigned char b);
	export escseq_manip background_color(unsigned char r, unsigned char g, unsigned char b);

	export enum class escseq_style : unsigned char {
		bold = 0b00000001,
		dim = 0b00000010,
		italic = 0b00000100,
		underline = 0b00001000,
		blink = 0b00010000,
		inverse = 0b00100000,
		hidden = 0b01000000,
		strikethrough = 0b10000000
	};

	export escseq_style operator|(escseq_style lhs, escseq_style rhs);
	export escseq_style operator&(escseq_style lhs, escseq_style rhs);

	export class style_manip {
	private:
		escseq_style flags;

	public:
		style_manip(escseq_style _flags) : flags(_flags) {}

		friend std::ostream& operator<<(std::ostream& out, const style_manip& manip);
	};

	export style_manip gen_style(escseq_style flags);

	export class reset_endl {
	private:
		bool fast = false;

	public:
		explicit reset_endl(bool _fast) : fast(_fast) {}

		friend std::ostream& operator<<(std::ostream& out, const reset_endl& manip);
	};

	export const reset_endl rendl(false);
	export const reset_endl rendl_fast(true);
}