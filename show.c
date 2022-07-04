#include <conio.h>
#include <graph.h>

void
show_bits(int bits)
{
    /* print the bits to the screen. assumes you've set up a text window
	and positioned the cursor first. */

    int shift;
    char on[1] = { 0xfe }; /* square */
    char off[1] = { 0xfa }; /* mid dot */

    for (shift = 7; shift >= 0; shift--) {
	if (bits & (1<<shift)) {
	    _outmem(on, 1);
	}
	else {
	    _outmem(off, 1);
	}
    }
}

void
clear_win(const char *title)
{
     /* assumes you've set up the window and colors first */

     _clearscreen(_GWINDOW);
     _settextposition(1,1);
     _outtext(title);
}

void
show_counter(int bits, int clear)
{
    /* print the counter to the screen. if clear is True, then clear
	the window before we use it. */

    _settextwindow(10,20, 12,30);
    _setbkcolor(5); /* magenta */

    if (clear) {
	_settextcolor(13); /* br magenta */
	clear_win("counter");
    }

    _settextcolor(15); /* br white */
    _settextposition(2,2); /* in the window */
    show_bits(bits);
}

void
show_memory(int bits, int clear)
{
    /* print the instr to the screen. if clear is True, then clear
	the window before we use it. */

    _settextwindow(10,35, 12,45);
    _setbkcolor(4); /* red */

    if (clear) {
	_settextcolor(12); /* br red */
	clear_win("instruction");
    }

    _settextcolor(15); /* br white */
    _settextposition(2,2);
    show_bits(bits);
}

void
show_accumulator(int bits, int clear)
{
    /* print the accum to the screen. if clear is True, then clear
	the window before we use it. */

    _settextwindow(20,35, 22,45);
    _setbkcolor(3); /* cyan */

    if (clear) {
	_settextcolor(11); /* br cyan */
	clear_win("accumulator");
    }

    _settextcolor(15); /* br white */
    _settextposition(2,2);
    show_bits(bits);
}
