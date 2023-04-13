Toy CPU
=======

A simulation of a Minimal Instruction Set Computer

Status
------

Working version (FreeDOS graphical mode)

License
-------

MIT

History
-------

I teach university courses part-time, including a class
about general computing topics, open to all majors. This
is an introductory course that teaches students about how
technology works, to remove the mystery around computing.

While not a computer science course, one section of this
course covers computer programming. I usually talk about
programming in very abstract terms, so I don't lose my
audience. But this year, I wanted my students to do some
"hands-on" programming in an "old school" way. At the
same time, I wanted to keep it simple, so everyone could
follow along.

I like to structure my lessons to show how you got from
"there" to "here." Ideally, I would let my students
learn how to write a simple program. Then I would pick
it up from there to show how modern programming allows
developers to create more complex programs. I decided to
try an unconventional approach - teach the students about
the ultimate in low-level programming: machine language.


How it works
------------

Early personal computers like the Apple II (1977), TRS-80
(1977), and IBM PC (1981) let users enter programs with a
keyboard, and displayed results on a screen. But computers
didn't always come with a screen and keyboard.

The Altair 8800 and IMSAI 8080 (both made in 1975) required
users to enter a program using "switches and lights" on a
panel. You would enter an instruction in machine language,
using a bank of switches, and the machine would light up
the ones and zeros of each binary instruction using LEDs.

Programming these early machines required knowing the
machine language instructions, called opcodes, short
for operation codes, to perform basic operations like
adding two numbers or storing a value into the computer's
memory. I wanted to show my students how programmers would
enter a series of instructions and memory addresses by
hand, using the switches and lights.

However, using an actual Altair 8800 would be too much
overhead in this class. I needed something simple that
any beginner-level student could grasp. Ideally, I hoped
to find a simple "hobby" retro computer that worked
similarly to the Altair 8800, but I couldn't find a
suitable "Altair-like" device for less than $100. I found
several "Altair" software emulators, but they faithfully
reproduce the Altair 8800 opcodes, and that was too much
for my needs.

I decided to write my own "educational" retro
computer. I call it the Toy CPU. You can find it on my
GitHub repository, including several releases to play
with. Version 1 was an experimental prototype that ran on
FreeDOS. Version 2 was an updated prototype that ran on
Linux with ncurses. Version 3 is a FreeDOS program that
runs in graphics mode.


Programming
-----------

The Toy CPU is a very simple retro computer. Sporting only
256 bytes of memory and a minimal instruction set, the Toy
CPU aims for simplicity while replicating the "switches and
lights" programming model. The interface mimics the Altair
8800, with a series of eight LEDs for the counter (the
"line number" for the program), instruction, accumulator
(internal memory used for temporary data), and status.

When you start the Toy CPU, it simulates "booting" by
clearing the memory. While the Toy CPU is starting up,
it also displays INI ("initialize") in the status lights
at the bottom-right of the screen. The PWR ("power")
light indicates the Toy CPU has been turned on.

When the Toy CPU is ready for you to enter a program,
it indicates INP ("input" mode) via the status lights,
and starts you at counter 0 in the program. Programs for
the Toy CPU always start at counter 0.

In "input" mode, use the up and down arrow keys to show
the different program counters, and press Enter to edit
the instruction at the current counter. When you enter
"edit" mode, the Toy CPU shows EDT ("edit" mode) on the
status lights.

The Toy CPU has a cheat sheet that's "taped" to the front
of the display. This lists the different opcodes the Toy
CPU can process:

<table>
<tr>
<th>opcode</th><th>Name</th><th>Description</th>
</tr>
<tr>
<th>00000000</th><td>STOP</td>
<td>Stop program execution.</td>
</tr>
<tr>
<th>00000001</th><td>RIGHT</td>
<td>Bit shift the accumulator to the right by 1 position. The value 00000010 becomes
00000001, and the value 00000001 becomes 00000000.</td>
</tr>
<tr>
<th>00000010</th><td>LEFT</td>
<td>Bit shift the accumulator to the left by 1 position. The value 00000010 becomes
00000100, and 10000000 becomes 00000000.</td>
</tr>
<tr>
<th>00001111</th><td>NOT</td>
<td>Binary NOT the accumulator. The value 10101111 becomes 01010000.</td>
</tr>
<tr>
<th>00010001</th><td>AND</td>
<td>Binary AND the accumulator with the value stored at an address.</td>
</tr>
<tr>
<th>00010010</th><td>OR</td>
<td>Binary OR the accumulator with the value stored at an address.</td>
</tr>
<tr>
<th>00010011</th><td>XOR</td>
<td>Binary XOR the accumulator with the value stored at an address.</td>
</tr>
<tr>
<th>00010100</th><td>LOAD</td>
<td>Load the accumulator with the value stored at an address.</td>
</tr>
<tr>
<th>00010101</th><td>STORE</td>
<td>Copy the accumulator into an address.</td>
</tr>
<tr>
<th>00010110</th><td>ADD</td>
<td>Add the value stored at an address to the accumulator.</td>
</tr>
<tr>
<th>00010111</th><td>SUB</td>
<td>Subtract the value stored at an address from the accumulator.</td>
</tr>
<tr>
<th>00011000</th><td>GOTO</td>
<td>Jump to a program address.</td>
</tr>
<tr>
<th>00011001</th><td>IFZERO</td>
<td>If the accumulator is zero, jump to a program address.</td>
</tr>
<tr>
<th>10000000</th><td>NOP</td>
<td>No operation; safely ignored.</td>
</table>

When in "edit" mode, use the left and right arrow keys
to select a bit in the opcode, and press Space to flip
the value between off (0) and on (1). When you are done
editing, press Enterto go back to "input" mode.

Sample programs
===============

Flash the lights
----------------

It helps to understand the Toy CPU by looking at a sample program. In
this example, we'll "flash" the accumulator lights. First we'll light
up the lower bits, then the higher bits, then all 8 bits. This tests
sequential operation of the Toy:

    0. LOAD
    1. "A" (7)
    2. LOAD
    3. "B" (8)
    4. LOAD
    5. "C" (9)
    6. STOP
    7. "A" = 00001111
    8. "B" = 11110000
    9. "C" = 11111111

This would be entered into the Toy like this:

    (counter: 00000000) instruction: 00010100
    (counter: 00000001) instruction: 00000111
    (counter: 00000010) instruction: 00010100
    (counter: 00000011) instruction: 00001000
    (counter: 00000100) instruction: 00010100
    (counter: 00000101) instruction: 00001001
    (counter: 00000110) instruction: 00000000
    (counter: 00000111) instruction: 00001111
    (counter: 00001000) instruction: 11110000
    (counter: 00001001) instruction: 11111111

This is a series of `LOAD` instructions that first loads the value
`00001111` into the acccumulator, effectively lighting up the right side
of the accumulator. Then it loads the value `11110000`, lighting up the
left side of the accumulator. Finally, it loads the value `11111111`,
lighting up all the lights on the accumulator.

Flash the lights (alternate method)
-----------------------------------

A more efficient way to write this program is to use logical operators to
operate on the initial `00001111` value. This loads `00001111` into the
accumulator, then performs a logical `NOT`, resulting in `11110000`. Then
it uses `OR` with the original `00001111` value to get `11111111` before
performing another `NOT` to give the final `00000000` result:

    0. LOAD
    1. "A" (7)
    2. NOT
    3. OR
    4. "A" (7)
    5. NOP
    6. STOP
    7. "A" = 00001111

If you want to edit a program that's already entered into memory, you may
need to use `NOP` statements to skip over now-unused instructions. In this
example, I modified the previous "Flash the lights" program, which had
`STOP` at instruction 6. Since the updated program ends at instruction 4,
I added a `NOP` statement at instruction 5 so the program would flow to
the `STOP` at instruction 6.

Move a light
------------

Or consider this sample program that moves a single light from the left
to the right:

    0. LOAD
    1. "A" (8)
    2. RIGHT ("loop start")
    3. IFZERO
    4. "end" (7)
    5. GOTO
    6. "loop start" (2)
    7. STOP ("end")
    8. "A" = 10000000

To make this program easier to read, I've added notes in parentheses for
the "loop start" at instruction 2, and "end" at instuction 7.  I always
write out my programs on paper first, and using this notation makes it
easier to go back later and fill in the instruction values. For example,
use the value `00000111` (7) at instruction 4, and the value `00000010`
(2) at instruction 6.

Countdown
---------

Or this sample program that counts down from 15:

    0. LOAD
    1. "A" (9)
    2. SUB ("loop start")
    3. "one" (10)
    4. IFZERO
    5. "end" (8)
    6. GOTO
    7. "loop start" (2)
    8. STOP ("end")
    9. "A" = 00001111 (15)
    10. "one" = 00000001 (1)

A + B = C
---------

Consider this short program that adds two values, "A" and "B," and stores
the result in the variable "C."

    0. LOAD
    1. "A" (7)
    2. ADD
    3. "B" (8)
    4. STORE
    5. "C" (9)
    6. STOP
    7. "A" = some number
    8. "B" = some other number
    9. "C" = placeholder

If you enter and run this program, you should see instruction 9 stores
the result of adding "A" and "B" together. It will be the same value as
the accumulator when the program has stopped running. Note that whatever
value was stored in "C" beforehand will be overwritten.

Compare A and B
---------------

Or this sample program that compares two numbers, "A" and "B." If they
are the same, the accumulator displays `00000000`. If they are different,
the accumulator displays `11111111`:

    0. LOAD
    1. "A" (9)
    2. XOR
    3. "B" (10)
    4. IFZERO
    5. "end" (8)
    6. LOAD
    7. "X" (11)
    8. STOP ("end")
    9. "A" = some number
    10. "B" = some other number
    11. "X" = 11111111
