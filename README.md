# Toy CPU

A simulation of a Minimal Instruction Set Computer

## Status

Unfinished prototype

## License

MIT

## History

I wanted to have a simple hobby "educational" computer, similar to
the Altair 8800, where you input a series of program instructions using
switches and LEDs, and run simple programs that way. Among other reasons,
I also wanted to use this as a demonstration for an undergraduate class
I teach about how technology works.

But I couldn't find a suitable "Altair-like" SBC for less than $100. There
are "Altair" software emulators out there, but they faithfully reproduce
the Altair 8800, and that was too much overhead for my needs.

So I decided to write my own hobby "educational" computer. I call it
the Toy CPU.

## How it works

I intentionally kept this as a very simple implementation. My goals were
to make it easy to write and easy to understand.

The Toy CPU implements 256 bytes of program memory, and an
accumulator. You program the Toy using binary opcodes. When you run a
program, the Toy CPU starts at `memory[0]` for the first instruction.

## Programming

I haven't implemented the "switches and LEDs" programming interface yet,
so for now, you have to use the *load_program()* function to load a
program into memory.

These are the opcodes for the Toy CPU, as currently implemented. (the
"." is for readability ... `0000.0000` means the 8-bit binary value
`00000000`.) Note that instructions that look like `0001.xxxx` take an
address as the next program instruction.

### 0000.0000 STOP ####

Stop program execution.

### 0000.0001 RIGHT ####

Bit shift the accumulator to the right by 1 position. `0000.0010` becomes
`0000.0001`, and `0000.0001` becomes `0000.0000`.

### 0000.0010 LEFT ###

Bit shift the accumulator to the left by 1 position. `0000.0010` becomes
`0000.0100`, and `1000.0000` becomes `0000.0000`.

### 0000.1111 NOT ###

Binary NOT the accumulator. `1010.1111` becomes `0101.0000`.

### 0001.0001 AND ###

Binary AND the accumulator with the value stored at an address.

### 0001.0010 OR ###

Binary OR the accumulator with the value stored at an address.

### 0001.0011 XOR ###

Binary XOR the accumulator with the value stored at an address.

### 0001.0100 LOAD ###

Load the accumulator with the value stored at an address.

### 0001.0101 STORE ###

Copy the accumulator into an address.

### 0001.0110 ADD ###

Add the value stored at an address to the accumulator.

### 0001.0111 SUB ###

Subtract the value stored at an address from the accumulator.

### 0001.1000 GOTO ###

Jump to a program address.

### 0001.1001 IFZERO

If the accumulator is zero, jump to a program address.


## Sample program ##

It helps to understand the Toy CPU by looking at a sample program. In
this example, we'll "flash" the accumulator lights. First we'll light
up the lower bits, then the higher bits, then all 8 bits. This tests
sequential operation of the Toy:

    memory[0] = 20; /* LOAD accum from addr */
    memory[1] = 7;
    memory[2] = 20; /* LOAD accum from addr */
    memory[3] = 8;
    memory[4] = 20; /* LOAD accum from addr */
    memory[5] = 9;
    memory[6] = 0;  /* STOP */
    memory[7] = 15;  /* 0000.1111 */
    memory[8] = 240; /* 1111.0000 */
    memory[9] = 255; /* 1111.1111 */

A more efficient way to write this program is to use logical operators to
operate on the initial `0000.1111` value. This loads `0000.1111` into the
accumulator, then performs a logical NOT, resulting in `1111.0000`. Then
it uses OR with the original `0000.1111` value to get `1111.1111` before
performing another NOT to give the final `0000.0000` result:

    memory[0] = 20; /* LOAD accum from addr */
    memory[1] = 7;
    memory[2] = 15; /* NOT */
    memory[3] = 18; /* OR accum with addr */
    memory[4] = 7;
    memory[5] = 15; /* NOT */
    memory[6] = 0;  /* STOP */
    memory[7] = 15;  /* 0000.1111 */

Or consider this sample program that moves a single light from the left
to the right:

    memory[0] = 20; /* LOAD accum from addr */
    memory[1] = 8;
    memory[2] = 1;  /* RIGHT shift */
    memory[3] = 25; /* IFZERO then goto addr */
    memory[4] = 7;
    memory[5] = 24; /* GOTO addr */
    memory[6] = 2;
    memory[7] = 0;  /* STOP */
    memory[8] = 128; /* 1000.0000 */
    
Or this sample program that counts down from 15:

    memory[0] = 20; /* LOAD accum from addr */
    memory[1] = 9;
    memory[2] = 23; /* SUBtract value at addr from accum */
    memory[3] = 10;
    memory[4] = 25; /* IFZERO then goto addr */
    memory[5] = 8;
    memory[6] = 24; /* GOTO addr */
    memory[7] = 2;
    memory[8] = 0;  /* STOP */
    memory[9] = 15; /* 0000.1111 */
    memory[10] = 1; /* "1" */

Or this sample program that compares two numbers, "A" and "B." If they
are the same, the accumulator displays `0000.0000`. If they are different,
the accumulator displays `1111.1111`:

    memory[0] = 20; /* LOAD accum from addr */
    memory[1] = 9;
    memory[2] = 19; /* XOR accum with value at addr */
    memory[3] = 10;
    memory[4] = 25; /* IFZERO then goto addr */
    memory[5] = 8;
    memory[6] = 20; /* LOAD accum from addr */
    memory[7] = 11;
    memory[8] = 0;  /* STOP */
    memory[9] = 12;   /* number "A" */
    memory[10] = 33;  /* number "B" */
    memory[11] = 255; /* 1111.1111 */
