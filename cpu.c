#if !defined(DEBUG)
#include <unistd.h> /* sleep */
#endif

#include "screen.h"
#include "cpuinstr.h"

int Accumulator;

/* functions to manage the CPU */

int
cpu_exec(int *mem, int count)
{
  int next;
  int addr;
  
  /* execute a single instruction from memory. implements a simple
     fetch/decode/execute model. fetch is the reference in the mem
     array. the decode is via a switch block. execute is each case in
     the switch block. */

  show_counter(count);
  show_instruction(mem[count]);

#if defined(DEBUG)
  getch();
#else
  sleep(1);
#endif

  /* returns the counter to the next instruction to execute. */

  next = (count<255 ? count+1 : 0);

  /* some operations require an address from the next program
     instruction. these instructions have the "fetch" bit set. */

  if (mem[count] & FETCH_BIT) {
    /* update the display */
    
    show_counter(next);
    show_instruction(mem[next]);

#if defined(DEBUG)
    getch();
#else
    sleep(1);
#endif

    /* advance the next counter */
    
    addr = mem[next];
    next = (next<255 ? next+1 : 0);
  }

  /* the switch block recognizes each CPU instruction as machine
     code. technically there is a NOP instruction, but it's not listed
     explicitly in the switch block because NOP is always ignored. any
     non-recognized instruction is effectively a NOP, but be careful
     for any unrecognized instructions that happen to have the "fetch"
     bit set, these cause an (unwanted) separate fetch of data. */

  switch(mem[count]) {
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
    
  case CPU_AND: /* binary AND the Accumulator with value at addr */
    Accumulator = Accumulator & mem[addr];
    break;
    
  case CPU_OR: /* binary OR the Accumulator with value at addr */
    Accumulator = Accumulator | mem[addr];
    break;
    
  case CPU_XOR: /* binary XOR the Accumulator with value at addr */
    Accumulator = Accumulator ^ mem[addr];
    break;
    
  case CPU_LOAD: /* load Accumulator with value at addr */
    Accumulator = mem[addr];
    break;
    
  case CPU_STORE: /* save Accumulator to addr */
    mem[addr] = Accumulator;
    break;
    
  case CPU_ADD: /* add value at addr to Accumulator */
    Accumulator += mem[addr];
    if (Accumulator > 255) {
      /* keep Accumulator in bounds 0 to 255 : 255 + 1 = 0 */
      Accumulator = Accumulator - 256;
    }
    break;
    
  case CPU_SUB: /* subtract value at addr from Accumulator */
    Accumulator -= mem[addr];
    if (Accumulator < 0) {
      /* keep Accumulator in bounds 0 to 255 : 0 - 1 = 255 */
      Accumulator = Accumulator + 256;
    }
    break;
    
  case CPU_GOTO: /* set next instr to addr */
    next = addr;
    
  case CPU_IFZERO: /* if Accumulator is zero, set next instr to addr */
    if (Accumulator == 0) {
      next = addr;
    }
  }

  /* update the display */

  show_accumulator(Accumulator);

#if defined(DEBUG)
  getch();
#else
  sleep(1);
#endif

  return next;
}

int
run_program(int *mem)
{
  /* execute a program from memory, starting at count=0 */

  int count = 0;

  print_message("run mode . . .");
  
  Accumulator = 0;
  show_accumulator(Accumulator);

  do {
    count = cpu_exec(mem, count);
  } while (count >= 0);

  print_message("done | press any key to enter program mode");
  getch();

  return Accumulator;
}
