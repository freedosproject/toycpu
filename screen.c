#include <curses.h> /* ncurses */
#include <string.h> /* strlen */

#include "bit.h"

WINDOW *win_counter;
WINDOW *win_instruction;
WINDOW *win_accumulator;

void
show_binary(WINDOW *win, int value)
{
  wmove(win, 2, 2);

  for (int bit = 7; bit >= 0; bit--) {
    waddch(win, ((1<<bit) & value) ? BIT_1 : BIT_0 );
  }
  wrefresh(win);
}

void
print_title(const char *title)
{
  attron(A_BOLD);
  
  mvaddstr(0, (COLS - strlen(title)) / 2, title);
  refresh();

  attroff(A_BOLD);
}

void
print_message(const char *msg)
{
  attron(A_REVERSE);

  mvhline(LINES-1, 0, ' ', COLS);

  mvaddstr(LINES-1, 0, msg);
  refresh();

  attroff(A_REVERSE);
}

void
print_instr(void)
{
  int row, col;

  row = LINES/5;
  col = COLS - 9 /* instr */ - 7 /* mnem */;

  attron(A_DIM);

  mvaddstr(row++, col, "........ STOP");

  mvaddstr(row++, col, ".......* RIGHT");
  mvaddstr(row++, col, "......*. LEFT");

  mvaddstr(row++, col, "....**** NOT");
  mvaddstr(row++, col, "...*...* AND");
  mvaddstr(row++, col, "...*..*. OR");
  mvaddstr(row++, col, "...*..** XOR");

  mvaddstr(row++, col, "...*.*.. LOAD");
  mvaddstr(row++, col, "...*.*.* STORE");

  mvaddstr(row++, col, "...*.**. ADD");
  mvaddstr(row++, col, "...*.*** SUB");

  mvaddstr(row++, col, "...**... GOTO");
  mvaddstr(row++, col, "...**..* IFZERO");

  mvaddstr(row++, col, "*....... NOP");

  attroff(A_DIM);
}

void
init_screen(void)
{
  /* init the screen */

  initscr();
  cbreak();
  noecho();

  /* title */

  print_title("Toy CPU Simulator");

  /* windows */

  win_counter = newwin(5, 12, LINES/5, COLS/4);
  box(win_counter, 0, 0);
  mvwaddstr(win_counter, 0, 1, "count");
  wrefresh(win_counter);

  win_instruction = newwin(5, 12, LINES/5, COLS/2);
  box(win_instruction, 0, 0);
  mvwaddstr(win_instruction, 0, 1, "instr");
  wrefresh(win_instruction);

  win_accumulator = newwin(5, 12, LINES/2, COLS/2);
  box(win_accumulator, 0, 0);
  mvwaddstr(win_accumulator, 0, 1, "accum");
  wrefresh(win_accumulator);

  /* init displays */

  /*
  show_binary(win_counter, 0);
  show_binary(win_instruction, 0);
  show_binary(win_accumulator, 0);
  */

  /* help */

#if defined(USE_HELP)
  print_instr();
#endif
}

void
end_screen(void)
{
  print_message("press any key to quit");
  getch();

  delwin(win_counter);
  delwin(win_instruction);
  delwin(win_accumulator);

  endwin();
}
