#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"    /* cpu virtual machine */
#include "show.h"   /* show cpu virtual machine */

#include "screen.h" /* screen control */

extern int *memory;

int
main()
{
    /* allocate memory */

    memory = calloc(256, sizeof(int));

    if (memory == NULL) {
	puts("out of memory");
	return 1;
    }

    if (init_screen() == 0) {
	puts("cannot set display");
	return 2;
    }

    /* set up the virtual machine */

    title("Toy CPU Simulator");
    init_vm();

/*
    blinkenlights(128);
*/
    load_program();
    run_program(0);

    /* done */

    end_screen();

    free(memory);

    return 0;
}
