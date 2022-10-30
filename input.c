#include <conio.h>
#include <graph.h>

#include "binary.h"
#include "screen.h"

void
erase_pointer(int shift)
{
#define INSTR_X 330
#define INSTR_Y 140
#define SIZE 32

    _setcolor(0); /* black */
    _rectangle(_GFILLINTERIOR, INSTR_X + (7-shift)*SIZE, INSTR_Y,
	INSTR_X + (7-shift)*SIZE + SIZE, INSTR_Y + 2);
}

void
show_pointer(int shift)
{
    _setcolor(15); /* br white */
    _rectangle(_GFILLINTERIOR, INSTR_X + (7-shift)*SIZE, INSTR_Y,
	INSTR_X + (7-shift)*SIZE + SIZE, INSTR_Y + 2);
}

int
edit_instruction(int instr)
{
    int key;
    int value, shift = 7;

    /* read an instruction value from the user, by simulating switches
	and lights */

    draw_status(STATUS_EDT); /* edit mode */

    value = instr;
    show_pointer(shift);

    do {
	key = getch();

	switch (key) {
	case 0: /* extended key .. call getch again */
	    switch ( getch() ) {
	    case 75: /* left .. increment shift */
		if (shift < 7) {
		    erase_pointer(shift);
		    show_pointer(++shift);
		}
		break;

	    case 77: /* right .. decrement shift */
		if (shift > 0) {
		    erase_pointer(shift);
		    show_pointer(--shift);
		}
	    }
	    break;

	case 32: /* space .. flip the bit value */
	    value = value ^ (1<<shift);
	    draw_instr(value);
	}
    } while (key != 13); /* 13 = Enter */

    erase_pointer(shift);
    return value;
}

int
input_program(int *mem, int start)
{
    int counter;
    int key;

    /* allow the user to step through the program memory, and select
	a program instruction to edit */

    draw_status(STATUS_INP); /* input mode */

    counter = start;

    draw_count(counter);
    draw_instr(mem[counter]);

    /* loop: select the instruction to edit */

    do {
	key = getch();

	switch (key) {
	case 0:
	    /* extended key .. call getch again */

	    switch ( getch() ) {
	    case 72: /* up .. decrement counter */
		if (counter > 0) {
		    draw_count(--counter);
		    draw_instr(mem[counter]);
		}
		break;

	    case 80: /* down .. increment counter */
		if (counter < 255) {
		    draw_count(++counter);
		    draw_instr(mem[counter]);
		}
	    }
	    break;

	case 13: /* enter .. edit this instruction */
	    mem[counter] = edit_instruction(mem[counter]);
	    draw_status(STATUS_INP); /* input mode */
	}
    } while ((key != 'r') && (key != 'R')
	    && (key != 'q') && (key != 'Q'));

    /* done when the user presses R (run) or Q (quit) */

    return key;
}
