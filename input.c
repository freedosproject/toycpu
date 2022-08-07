#include <curses.h>

#include "bit.h"
#include "screen.h"

int
get_binary(WINDOW *win, int initval)
{
  int key;
  int num;
  int bit = 7;
  
  num = initval;

  keypad(win, TRUE);
  intrflush(win, FALSE);

  /* set bold, so we know we are in "input" mode */
  
  wattron(win, A_BOLD);
  show_binary(win, num);

  /* read a binary value from the user, by simulating switches and
     lights on a dashboard */

  do {
    wmove(win, 2, 2 + 7-bit); /* position cursor over the switch */
    key = wgetch(win);

    switch(key) {
    case '-':
    case KEY_LEFT: /* left: move key bit left (higher) */
      bit = (bit<7 ? bit+1 : 7);
      break;

    case '+':
    case KEY_RIGHT: /* right: move key bit right (lower) */
      bit = (bit>0 ? bit-1 : 0);
      break;
      
    case ' ': /* space bar */
      /* flip the bit */
      num = num ^ (1<<bit);
      waddch(win, (num & (1<<bit)) ? BIT_1 : BIT_0);
    }
  } while ((key != KEY_ENTER) && (key != '\n'));

  /* show the result in normal text */
  
  wattroff(win, A_BOLD);
  show_binary(win, num);

  return num;
}

int
input_program(int *mem)
{
  int key;
  int count = 0;

  keypad(win_counter, TRUE);
  intrflush(win_counter, FALSE);

  /* allow the user to enter a program in binary. enter 'R' to return
     and run program. */

  print_message("program mode | up/down = prev/next | enter = input | R = run | Q = quit");

  do {
    show_instruction(mem[count]);
    show_counter(count); /* draw this last so the cursor is shown there */

    key = wgetch(win_counter);

    switch(key) {
    case '-':
    case KEY_UP: /* up: go to previous instruction in memory */
      count = (count>0 ? count-1 : 0);
      break;

    case '+':
    case KEY_DOWN: /* down: go to next instruction in memory */
      count = (count<255 ? count+1 : 255);
      break;

    case '\n':
    case KEY_ENTER: /* change this instruction in memory */
      print_message("input mode | left/right = prev/next | space = flip | enter = done");
      mem[count] = get_binary(win_instruction, mem[count]);
      print_message("program mode | up/down = prev/next | enter = input | R = run | Q = quit");
    }
  } while ((key != 'r') && (key != 'R')
	   && (key != 'q') && (key != 'Q'));

  return key;
}
