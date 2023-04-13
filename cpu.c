#include <conio.h> /* kbhit, getch */

#include "binary.h"
#include "screen.h"

#include "cpu.h"
#include "opcodes.h"

int Accumulator;

int
next_instruction(int counter)
{
    /* the next instruction to execute */

    if (counter < 255) {
	return counter+1;
    }

    /* else, loop back around to zero (keep in 0 to 255: 255+1=0) */

    draw_status(STATUS_ERR | STATUS_RUN); /* overflow */
    return 0;
}

int
run_instruction(int *mem, int counter)
{
    int next, addr;

    /* execute a single instruction from memory. implements a single
	fetch/decode/execute model. fetch is the reference from mem,
	decode is via the switch block, execute is each case in the
	switch block. */

    draw_count(counter);
    draw_instr(mem[counter]);
    tick();

    next = next_instruction(counter);

    /* some operations require an address from the next program
	instruction. these instructions have a "fetch" bit set. */

    if (mem[counter] & FETCH_BIT) {
	draw_count(next);
	draw_instr(mem[next]);
	tick();

	addr = mem[next]; /* set the address value */
	next = next_instruction(next); /* set the next instruction */
    }

    /* the switch block recognizes each CPU instruction as a CPU
	opcode, written in machine language (binary).

	technically, there is a NOP instruction, but it's not
	listed here because any unrecognized opcode is considered
	a NOP instruction. BE CAREFUL OF USING UNRECOGNIZED
	OPCODES WITH THE FETCH BIT SET, these will also advance
	the next counter, and will result in a programming bug. */

    switch(mem[counter]) {
    case CPU_STOP:
	return -1;

    case CPU_RIGHT:
	Accumulator = Accumulator>>1;
	break;

    case CPU_LEFT:
	Accumulator = Accumulator<<1;
	break;

    case CPU_NOT:
	Accumulator = ~Accumulator;
	break;

    case CPU_AND:
	Accumulator = Accumulator & mem[addr];
	break;

    case CPU_OR:
	Accumulator = Accumulator | mem[addr];
	break;

    case CPU_XOR:
	Accumulator = Accumulator ^ mem[addr];
	break;

    case CPU_LOAD:
	Accumulator = mem[addr];
	break;

    case CPU_STORE:
	mem[addr] = Accumulator;
	break;

    case CPU_ADD:
	Accumulator += mem[addr];

	if (Accumulator > 255) {
	    Accumulator -= 256; /* keep accum in bounds 0 to 255: 255+1=0 */
	    draw_status(STATUS_ERR | STATUS_RUN); /* overflow */
	}
	break;

    case CPU_SUB:
	Accumulator -= mem[addr];

	if (Accumulator < 0) {
	    Accumulator += 256; /* keep accum in bounds 0 to 255: 0-1=255 */
	    draw_status(STATUS_ERR | STATUS_RUN); /* underflow */
	}
	break;

    case CPU_GOTO:
	next = addr;
	break;

    case CPU_IFZERO:
	if (Accumulator == 0) {
	    next = addr;
	}
    }

    Accumulator &= 255; /* keep accum in bounds 0 to 255: 11111111 */

    /* update the display */

    draw_accum(Accumulator);
    tick();

    return next;
}

int
run_program(int *mem, int start)
{
    int key;
    int counter;

    draw_status(STATUS_RUN); /* run mode */

    /* run the program */

    Accumulator = 0;
    draw_accum(Accumulator);

    counter = start;

    do {
	counter = run_instruction(mem, counter);

	/* do we need to abort? */

	if (kbhit()) {
	    key = getch();

	    if (key==0) {
		/* getch returns zero if extended key .. call getch
		    again to clear it */
		getch();
	    }
	    else if (key == 27) { /* ESC key */
		draw_status(STATUS_ABT | STATUS_RUN);
		tick();

		return Accumulator;
	    }
	}
    } while (counter >= 0);

    tick();

    return Accumulator;
}
