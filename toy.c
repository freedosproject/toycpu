#include <stdio.h>
#include <stdlib.h> /* calloc, free */

#include <conio.h>
#include <graph.h>

#include "binary.h"
#include "screen.h"

#include "input.h"
#include "cpu.h"

void
init_vm(int *mem)
{
    int count;


    /* light up the blinkenlights */

    draw_status(STATUS_PWR); /* turn on power */

    draw_accum(0); /* accumulator is zero */

    draw_instr(0); /* set every instruction to zero */

    /* set every instruction to zero */

    draw_status(STATUS_INI); /* initialize */

    for (count = 0; count < 256; count++) {
	draw_count(count);
	mem[count] = 0;
    }
}

int
main()
{
    int *mem;
    int input;
    int count;

    /* allocate memory: 0..255 integer instructions */

    mem = calloc(256, sizeof(int));

    if (mem == NULL) {
	puts("Cannot allocate memory: 256 bytes");
	return EXIT_FAILURE;
    }

    /* set up the screen */

    if (init_screen() == 0) {
	puts("Cannot set video mode: 640x480 @ 16 colors");
	return EXIT_FAILURE;
    }

    /* start up the VM */

    init_vm(mem);

    /* input and run the program */

    do {
	input = input_program(mem, 0);

	if ((input == 'r') || (input == 'R')) {
	    /* entered, now run starting at zero */
	    run_program(mem, 0);
	}
    } while ((input != 'q') && (input != 'Q'));

    /* done */

    draw_status(STATUS_HLT);

    tick(); /* tick of CPU clock */

    /* no one will see the status lights turn off because it will be
	so fast, but it makes me happy to do this */

    draw_count(0);
    draw_instr(0);
    draw_accum(0);
    draw_status(STATUS_OFF);

    end_screen();

    /* debugging: dump the program */

/*
    puts("Debugging:");
    for (count = 0; count < 20; count++) {
	printf("mem[%d] = %d\n", count, mem[count]);
    }
*/

    free(mem);

    return EXIT_SUCCESS;
}
