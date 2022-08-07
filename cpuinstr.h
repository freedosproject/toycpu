/* 0000 0000 = STOP execution */
#define CPU_STOP  0

/* 0000 0001 = shift bits RIGHT by 1 */
#define CPU_RIGHT 1
/* 0000 0010 = shift bits LEFT by 1 */
#define CPU_LEFT  2

/* 0000 1111 = binary NOT the accum */
#define CPU_NOT   15
/* 0001 0001 = binary AND the accum with value at addr */
#define CPU_AND   17
/* 0001 0010 = binary OR the accum with value at addr */
#define CPU_OR    18
/* 0001 0011 = binary XOR the accum with value at addr */
#define CPU_XOR   19

/* 0001 0100 = LOAD accum from value at addr */
#define CPU_LOAD  20
/* 0001 0101 = STORE accum into addr */
#define CPU_STORE 21

/* 0001 0110 = ADD value at addr to accum */
#define CPU_ADD   22
/* 0001 0111 = SUBtract value at addr from accum */
#define CPU_SUB   23

/* 0001 1000 = GOTO program instr at addr */
#define CPU_GOTO  24
/* 0001 1001 = IF accum is ZERO, goto program instr at addr */
#define CPU_IFZERO 25

/* 1000 0000 = NOP (ignore this instruction) */
#define CPU_NOP   128

/* 0001 0000 = bit indicates CPU should pre-fetch next instr */
#define FETCH_BIT 16
