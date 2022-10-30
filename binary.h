#if !defined(BINARY_H)
#define BINARY_H

void
draw_binary(int x, int y, int size, int val);

/* macros to draw the Counter, Instruction, and Accumulator */

#define draw_count(C) draw_binary(54, 100, 32, C)
#define draw_instr(I) draw_binary(330, 100, 32, I)
#define draw_accum(A) draw_binary(330, 200, 32, A)
#define draw_status(S) draw_binary(330, 300, 32, S)

/* status codes (to show in binary) */

#define STATUS_OFF 0
#define STATUS_PWR 1
/* all other status codes should show power on (add one) */
#define STATUS_INP 3
#define STATUS_EDT 5
#define STATUS_RUN 9
#define STATUS_ABT 17
#define STATUS_ERR 33
#define STATUS_HLT 65
#define STATUS_INI 129

#endif
