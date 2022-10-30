#if !defined(CPU_H)
#define CPU_H

int
run_program(int *mem, int start);

#include <i86.h> /* delay */

/* half a second (500ms) */
/* #define tick() (delay(500)) */

/* one second (1000ms) */
#define tick() (delay(1000))

/* two seconds (2000ms) */
/* #define tick() (delay(2000)) */

#endif
