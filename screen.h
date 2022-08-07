#include <curses.h>

/* show binary values in a window: */

void show_binary(WINDOW *win, int value);

extern WINDOW *win_counter;
extern WINDOW *win_instruction;
extern WINDOW *win_accumulator;

#define show_counter(C)     show_binary(win_counter, C)
#define show_instruction(I) show_binary(win_instruction, I)
#define show_accumulator(A) show_binary(win_accumulator, A)

/* message display functions: */

void print_title(const char *title);
void print_message(const char *msg);

/* screen init functions: */

void init_screen(void);
void end_screen(void);
