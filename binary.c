#include <conio.h>
#include <graph.h>

void
draw_bit(int x, int y, int size, int bit)
{
    /* bit is zero or nonzero */

    /* draw outline */

    _setcolor(4); /* red */
    _ellipse(_GFILLINTERIOR, x, y, x+size, y+size);

    /* draw interior */

    if (bit) {
	_setcolor(12); /* br red */
    }
    else {
	_setcolor(0); /* black */
    }

    _ellipse(_GFILLINTERIOR, x+2, y+2, x+size-2, y+size-2);

    /* draw highlight */

    _setcolor(4); /* red */
    _ellipse(_GFILLINTERIOR, x + size/4, y + size/4,
	x + size*2/3, y + size/2);

    /* erase part of the highlight */

    if (bit) {
	_setcolor(12); /* br red */
    }
    else {
	_setcolor(0); /* black */
    }

    _ellipse(_GFILLINTERIOR, x + size/3, y + size/3,
	x + size*3/4, y + size*2/3);
}

void
draw_binary(int x, int y, int size, int val)
{
    int shift;

    for (shift = 0; shift < 8; shift++) {
	/* 1<<0 = 00000001 and 1<<7 = 10000000 */
	draw_bit(x + (7-shift)*size, y, size, (1<<shift) & val);
    }
}
