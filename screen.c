#include <string.h> /* strlen */
#include <conio.h>
#include <graph.h>

void
print_title(const char *title)
{
    _setcolor(11); /* br cyan */

    /* approx center the title: the screen is 640x480, so center is
	320. text is 8x8, so half the string length is:
	strlen(title)*8/2 = strlen(title)*4 */

    _moveto(320 - strlen(title)*4, 1);
    _outgtext(title);
}

void
print_message(const char *message)
{
    /* draw a box .. this also clears the message area */

    _setcolor(1); /* blue */
    _rectangle(_GFILLINTERIOR, 0, 470, 639, 479);

    /* print the text */

    _setcolor(7); /* white */
    _moveto(4, 471);
    _outgtext(message);
}

void
pause(const char *msg)
{
    if (msg == NULL) {
	print_message("Press any key...");
    }
    else {
	print_message(msg);
    }

    /* getch() returns zero if an extended key. call getch() again to
	get the extended value. in this case, we're just waiting for a
	key, so call again anyway if getch() is zero, to clear the ext
	key value. */

    if (getch() == 0) {
	getch();
    }
}

int
init_screen()
{
    int lines;

    /* set up the video mode: 640x480 @ 16 colors */

    lines = _setvideomode(_VRES16COLOR);

    if (lines == 0) {
	return 0;
    }

    /* set up the user interface */

    /* two-tone border around the screen, with 20px border and 10px
	reveal. add an extra 200px x 20px space on the upper-left
	of the screen for the program title, and 100px extra space
	on the bottom for hinting. */

    _setcolor(1); /* blue */

#define XRES 639
#define YRES 479

    /* top */
    _rectangle(_GFILLINTERIOR, 0, 0, XRES, 20);
    /* left */
    _rectangle(_GFILLINTERIOR, 0, 0, 20, YRES);
    /* right */
    _rectangle(_GFILLINTERIOR, XRES-20, 0, XRES, YRES);
    /* bottom */
    _rectangle(_GFILLINTERIOR, 0, YRES-100-10, XRES, YRES);
    /* title */
    _rectangle(_GFILLINTERIOR, 0, 0, 200+10, 20+10);
    /* rounded corner (title) */
    _ellipse(_GFILLINTERIOR, 200+10-20, 10, 200+10+20, 10+20);

    _setcolor(3); /* cyan */

    /* top */
    _rectangle(_GFILLINTERIOR, 0, 0, XRES, 10);
    /* left */
    _rectangle(_GFILLINTERIOR, 0, 0, 10, YRES);
    /* right */
    _rectangle(_GFILLINTERIOR, XRES-10, 0, XRES, YRES);
    /* bottom */
    _rectangle(_GFILLINTERIOR, 0, YRES-100, XRES, YRES);
    /* title */
    _rectangle(_GFILLINTERIOR, 0, 0, 200, 20);
    /* rounded corner (title) */
    _ellipse(_GFILLINTERIOR, 200-20, 0, 200+20, 20);

    /* print title */

    _setcolor(11); /* br cyan */
    _moveto(46, 6);
    _outgtext("Toy CPU Simulator");

    /* print hints */

    /*
	\030 = up, \031 = down, \032 = right, \033 = left
	\022 = up/down,  \035 = left/right
	\263 = vert bar, \304 = horiz bar
	\371 = bullet,   \372 = middot
    */

    _moveto(130, YRES-80);
    _outgtext("Input mode: \022 \372 counter \263 Enter \372 edit \263 R \372 run \263 Q \372 quit");

    _moveto(130, YRES-60);
    _outgtext("Edit mode: \035 \372 bit \263 Space \372 flip \263 Enter \372 done");

    /* print labels */

    _setcolor(8); /* br white */

    _moveto(54, 90);
    _outgtext("Counter");

    _moveto(330, 90);
    _outgtext("Instruction");

    _moveto(330, 190);
    _outgtext("Accumulator");

    /* LEDs are 32px wide, text is 8x8, so three letters plus a space
	is 32px. offset by 4px to center the text over each LED. */

    _moveto(334, 290);
    _outgtext("INI HLT ERR ABT RUN EDT INP PWR");

    /* print cheat sheet */

    /*
	\371 = bullet,   \372 = middot
	\376 = square
    */

    _setcolor(7); /* white */
    _rectangle(_GFILLINTERIOR, 50, 200, 230, 356); /* "paper" */

    _setcolor(8); /* br black */
    _rectangle(_GFILLINTERIOR, 125, 195, 150, 205); /* "tape" */

    _setcolor(0); /* black */
    _moveto(60, 210);
    _outgtext("\372\372\372\372\372\372\372\372 STOP");
    _moveto(60, 220);
    _outgtext("\372\372\372\372\372\372\372\376 RIGHT");
    _moveto(60, 230);
    _outgtext("\372\372\372\372\372\372\376\372 LEFT");
    _moveto(60, 240);
    _outgtext("\372\372\372\372\376\376\376\376 NOT");
    _moveto(60, 250);
    _outgtext("\372\372\372\376\372\372\372\376 AND addr");
    _moveto(60, 260);
    _outgtext("\372\372\372\376\372\372\376\372 OR addr");
    _moveto(60, 270);
    _outgtext("\372\372\372\376\372\372\376\376 XOR addr");
    _moveto(60, 280);
    _outgtext("\372\372\372\376\372\376\372\372 LOAD addr");
    _moveto(60, 290);
    _outgtext("\372\372\372\376\372\376\372\376 STORE addr");
    _moveto(60, 300);
    _outgtext("\372\372\372\376\372\376\376\372 ADD addr");
    _moveto(60, 310);
    _outgtext("\372\372\372\376\372\376\376\376 SUB addr");
    _moveto(60, 320);
    _outgtext("\372\372\372\376\376\372\372\372 GOTO addr");
    _moveto(60, 330);
    _outgtext("\372\372\372\376\376\372\372\376 IFZERO addr");
    _moveto(60, 340);
    _outgtext("\376\372\372\372\372\372\372\372 NOP");

    return lines;
}
