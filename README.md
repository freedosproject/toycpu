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

I teach university courses part-time, and one course that I teach is
MIS 100, where students learn how technology works. For our section on
"programming," I usually talk about programming in very abstract terms,
because these are not Computer Science students. But this year, I wanted
to try something new.

I hoped to start the "programming" discussion by walking my students
through a history of programming, so they could see the next step
and how that worked. I tried to find a simple hobby "educational"
computer, similar to the Altair 8800, where you input a series of program
instructions in "machine language" (binary opcodes) using switches and
LEDs. I wanted the instructions to be simple enough that my students could
write a few simple programs, like `A+B=C`, and use that as a starting
point to write the same program in Assembly, and in C, and ... you get
the idea.

But I couldn't find a suitable "Altair-like" SBC for less than $100. There
are "Altair" software emulators out there, but they faithfully reproduce
the Altair 8800, and that was too much overhead for my needs.

So I decided to write my own hobby "educational" computer. I call it
the Toy CPU.

I wrote a rough prototype on DOS using character mode, but you couldn't
enter a program on the "front panel."  Instead, you had to hard-code a
program into memory, and recompile to run that. It was very primitive,
but enough to know that it worked.

Later, I completely rewrote the Toy CPU using Linux ncurses. This was
still a prototype, but this time you could enter a program on the "front
panel" by "flipping bits." It looked okay in ncurses, but I really wanted
a graphical program.

Open Jam 2022 came up at the right time! I decided to completely
rewrite the Toy from scratch, using FreeDOS and other open source
tools. I don't use graphical assets per se; instead, the Toy draws the
interface elements using basic graphical functions from OpenWatcom (open
source). If you're curious: I used FED (open source) as my editor. I ran
FreeDOS inside VirtualBox (open source) running on top of Fedora Linux
(open source). Everything in the pipeline was open source.

The theme for Open Jam 2022 is "Light in the Darkness," which is a
perfect fit for the Toy CPU, because of all the blinkenlights!

How it works
------------

I intentionally kept this as a very simple implementation. My goals were
to make it easy to write and easy to understand.

The Toy CPU implements 256 bytes of program memory, and an
accumulator. You program the Toy using binary opcodes. When you run a
program, the Toy CPU starts at counter zero for the first instruction.

Programming
-----------

When you start the Toy, it will "boot up" by clearing all the values in
the 256-byte memory. You'll see it count up from 0 to 255 in the counter
display, while the instruction and accumulator displays remain at zero.

Look at the status display on the bottom-right of the Toy. You will see
"PWR" when the Toy is turned on, and "INI" when the Toy is initializing.

After initialization, you'll be put into Input mode. Look on the status
display and you will see "INP" light up to indicate you are in Input mode.

In Input mode, you enter a program using "switches and lights" on the
front panel, similar to computers in the 1960s or 1970s. Use the Up/Down
arrow keys to select the instruction you want to edit, then press Enter
to edit an instruction.

Look on the status display, and you will see "EDT" light up to show you
are in Edit mode.

In Edit mode, use the Left/Right arrow keys to select a bit in the
instruction, and hit Space to flip a specific bit in an instruction.
When you're done entering an intruction, press Enter to go back to
Input mode.

From Input mode, press `R` to run the program. This always runs the
program from the first instruction. The status display will light up
"RUN" when the Toy runs your program.

If you need to abort your program, press the Esc key during program
execution and the Toy will light up the "ABT" in the status display
before it drops you back into Input mode.

To exit the Toy, press `Q` while in Input mode. The Toy will light up the
"HLT" light on the status and then will quit to DOS.

Here are the opcodes for the Toy CPU, as currently implemented:

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

Any other unrecognized instruction is the equivalent of a `NOP`. However,
do not rely on other opcodes being the same as `NOP`. For example, in
the current version of the Toy, any instruction with `...1....` will
also perform an extra fetch operation.

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
