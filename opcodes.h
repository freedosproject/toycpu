#if !defined(OPCODES_H)
#define OPCODES_H

/* opcodes */

/* .... .... stop execution */
#define CPU_STOP 0

/* .... ...1 shift accum bits right by one */
#define CPU_RIGHT 1
/* .... ..1. shift accum bits left by one */
#define CPU_LEFT 2
/* .... 1111 binary NOT the accum */

#define CPU_NOT 15
/* ...1 ...1 binary AND accum with addr */
#define CPU_AND 17
/* ...1 ..1. binary OR accum with addr */
#define CPU_OR 18
/* ...1 ..11 binary XOR accum with addr */
#define CPU_XOR 19

/* ...1 .1.. load accum from value at addr */
#define CPU_LOAD 20
/* ...1 .1.1 store accum into addr */
#define CPU_STORE 21

/* ...1 .11. add value at addr to accum */
#define CPU_ADD 22
/* ...1 .111 subtract value at addr from accum */
#define CPU_SUB 23

/* ...1 1... goto (jump to) program instr at addr */
#define CPU_GOTO 24
/* ...1 1..1 if accum is zero, goto program instr at addr */
#define CPU_IFZERO 25

/* 1... .... null operation (NOP) */
#define CPU_NOP 128

/* ...1 .... fetch bit */
#define FETCH_BIT 16

#endif
