#include <conio.h>
#include <graph.h>

#include <i86.h> /* delay, sound */

#include "screen.h"
#include "show.h"

/* theory of operation:

    the Toy CPU is a simple approximation of a cpu from the 1960s or
    1970s. this implements the virtual machine as 256 bytes of program
    memory (from 0 to 255) which you can use for program instructions
    and variable storage. the accumulator is separate memory.

    each "tick" of the cpu fetches an instruction from memory, then
    executes it. note that some instructions take an addr, which is
    another fetch from program memory.

    the Toy CPU displays the binary representations of the program
    counter, the current instruction from memory at that counter
    location, and the accumulator.
*/

int *memory;
int counter;
int accumulator;

void
init_vm(void)
{
    /* assign zero to everything */

    for (counter = 0; counter < 256; counter++) {
	memory[counter] = 0;
    }

    counter = 0;
    accumulator = 0;

    show_counter(counter, 1);
    show_memory(memory[counter], 1);
    show_accumulator(0, 1);
}

void
tick(int freq)
{
    if (freq>0) {
	sound(freq);
	delay(10);
    }

#if defined(DELAY)
    delay(500); /* milliseconds */
#else
    message("press any key for next instr . . .");
    pause(); /* wait for user */
#endif
}

int
next_addr(int addr)
{
    /* what is the addr after this one? */
    return (addr<255 ? addr+1 : 0);
}

int
prev_addr(int addr)
{
    /* what is the addr before this one? */
    return (addr>0 ? addr-1 : 255);
}

int
fetch_execute(int addr)
{
    int instr;
    int next;

    int addr2;
    int mem_addr2;

    /* execute an instruction at addr. returns the addr of the next
	instruction, or -1 if stop. */

    /* always mask values with 1111.1111 (255) to ensure the bits
	stay in range */

    /* FETCH the instruction */

    instr = 255 & memory[addr];

    next = next_addr(addr); /* set the next addr */

    show_counter(addr, 0);
    show_memory(instr, 0);
    show_accumulator(accumulator, 0);
    tick(0);

    /* if xxx1.xxxx then the next item is an addr to use */

    if (instr & 16) { /* 0001.0000 */
	/* FETCH the next item */

	/* THERE'S A BUG HERE: for a bad instr that happens to have
	    bit xxx1.xxxx set (like 1111.1111 = 255) the display
	    gets updated the next instr, but the Toy actually fails
	    on the "255" instruction. so the display doesn't show
	    the instr that caused the abort. */

	addr2 = 255 & memory[next]; /* the addr from the next instr */
	mem_addr2 = memory[addr2];  /* the value at addr */

	show_counter(next, 0);
	show_memory(addr2, 0);
	tick(0);

	next = next_addr(next);     /* set the next addr */
    }

    /* EXECUTE the instruction */

    switch(instr) {
    case  0: /* 0000.0000 STOP */
	message("stop - press a key to continue . . .");
	pause();
	return -1;
    case  1: /* 0000.0001 RIGHT */
	accumulator = 255 & (accumulator>>1);
	return next;
    case  2: /* 0000.0010 LEFT */
	accumulator = 255 & (accumulator<<1);
	return next;
    case 15: /* 0000.1111 NOT */
	accumulator = 255 & (~accumulator);
	return next;
    case 17: /* 0001.0001 AND */
	accumulator = 255 & (accumulator & mem_addr2);
	return next;
    case 18: /* 0001.0010 OR */
	accumulator = 255 & (accumulator | mem_addr2);
	return next;
    case 19: /* 0001.0011 XOR */
	accumulator = 255 & (accumulator ^ mem_addr2);
	return next;
    case 20: /* 0001.0100 LOAD */
	accumulator = 255 & mem_addr2;
	return next;
    case 21: /* 0001.0101 STORE */
	memory[addr2] = 255 & accumulator;
	return next;
    case 22: /* 0001.0110 ADD */
	accumulator = 255 & (accumulator + mem_addr2);
	return next;
    case 23: /* 0001.0111 SUB */
	accumulator = 255 & (accumulator - mem_addr2);
	return next;
    case 24: /* 0001.1000 GOTO */
	return addr2;
    case 25: /* 0001.1001 IFZERO */
	if (accumulator == 0) {
	    return addr2;
	}
	return next;
    default:
	error("invalid opcode - press a key to continue . . .");
	pause();
	return -1;
    }
}

void
run_program(int start)
{
    int next;

    message("running . . .");

    next = fetch_execute(start);

    while (next >= 0) {
	next = fetch_execute(next);
    }
}

void
load_program(void)
{
    /* load a hard-wired program into memory */

    message("loading program . . .");

#if 0
    /* immediately fail with invalid instr */

    memory[0] = 8; /* there is no 0000.1000 instruction */
#endif

#if 0
    /* flash the blinkenlights */

    memory[0] = 20; /* LOAD accum from addr */
    memory[1] = 7;
    memory[2] = 20; /* LOAD accum from addr */
    memory[3] = 8;
    memory[4] = 20; /* LOAD accum from addr */
    memory[5] = 9;
    memory[6] = 0;  /* STOP */
    memory[7] = 15;  /* 0000.1111 */
    memory[8] = 240; /* 1111.0000 */
    memory[9] = 255; /* 1111.1111 */
#endif

#if 1
    /* move a blinkenlight from left to right */

    memory[0] = 20; /* LOAD accum from addr */
    memory[1] = 8;
    memory[2] = 1;  /* RIGHT shift */
    memory[3] = 25; /* IFZERO then goto addr */
    memory[4] = 7;
    memory[5] = 24; /* GOTO addr */
    memory[6] = 2;
    memory[7] = 0;  /* STOP */
    memory[8] = 128; /* 1000.0000 */
#endif

#if 0
    /* count down from 15 (0000.1111) */

    memory[0] = 20; /* LOAD accum from addr */
    memory[1] = 9;
    memory[2] = 23; /* SUBtract value at addr from accum */
    memory[3] = 10;
    memory[4] = 25; /* IFZERO then goto addr */
    memory[5] = 8;
    memory[6] = 24; /* GOTO addr */
    memory[7] = 2;
    memory[8] = 0;  /* STOP */
    memory[9] = 15; /* 0000.1111 */
    memory[10] = 1; /* "1" */
#endif

#if 0
    /* compare two numbers (0's if equal, 1's if not equal) */

    memory[0] = 20; /* LOAD accum from addr */
    memory[1] = 9;
    memory[2] = 19; /* XOR accum with value at addr */
    memory[3] = 10;
    memory[4] = 25; /* IFZERO then goto addr */
    memory[5] = 8;
    memory[6] = 20; /* LOAD accum from addr */
    memory[7] = 11;
    memory[8] = 0;  /* STOP */
    memory[9] = 12;   /* number "A" */
    memory[10] = 33;  /* number "B" */
    memory[11] = 255; /* 1111.1111 */
#endif
}

void
blinkenlights(int count)
{
    int num;

    /* exercise the blinkenlight, up to a max count */

    message("enjoy the blinkenlights . . .");

    for (num = 0; num <= count; num++) {
	show_counter(num, 0);
	show_memory(num, 0);
	show_accumulator(num, 0);

	tick(0);
    }

    message("Ok");
    pause();
}
