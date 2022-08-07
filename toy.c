#include <stdio.h>
#include <stdlib.h>

#include "screen.h"
#include "input.h"
#include "cpu.h"

int
main()
{
  int inp;
  int *mem;
  
  /* allocate memory */

  mem = calloc(256, sizeof(int));

  if (mem == NULL) {
    puts("out of memory");
    return EXIT_FAILURE;
  }

  for (int count = 0; count < 256; count++) {
    mem[count] = 0;
  }

  /* initialize the virtual machine */

  init_screen();

  /* input and run program */

  do {
    inp = input_program(mem);

    if ((inp == 'r') || (inp == 'R')) {
      run_program(mem);
    }
  } while ((inp != 'q') && (inp != 'Q'));

  /* done */

  end_screen();

#if defined(DEBUG)
  puts("debugging: first 10 program lines");

  for (int count = 0; count < 10; count++) {
    printf("%d: 0x%2.2x\n", count, mem[count]);
  }
#endif

  free(mem);
  
  return EXIT_SUCCESS;
}
