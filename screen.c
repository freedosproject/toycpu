#include <string.h> /* strlen */

#include <conio.h>
#include <graph.h>

void
title(const char *t)
{
    _settextwindow(1,1, 1, 80);
    _setbkcolor(1); /* cyan */
    _clearscreen(_GWINDOW);

    _settextcolor(7); /* white */
    _settextposition(1, 40 - strlen(t)/2); /* in the window */
    _outtext(t);
}

void
message(const char *m)
{
    _settextwindow(25,1, 25,80);
    _setbkcolor(7); /* white */
    _clearscreen(_GWINDOW);

    _settextcolor(1); /* blue */
    _settextposition(1, 2); /* in the window */
    _outtext(m);
}

void
error(const char *m)
{
    _settextwindow(25,1, 25,80);
    _setbkcolor(4); /* red */
    _clearscreen(_GWINDOW);

    _settextcolor(14); /* yellow */
    _settextposition(1, 2); /* in the window */
    _outtext(m);
}

void
pause(void)
{
    if (getch() == 0) {
	getch();
    }
}

int
init_screen(void)
{
    /* set up the screen */

    if (_setvideomode(_TEXTC80) == 0) {
	return 0;
    }

    _displaycursor(_GCURSOROFF);

    return 25;
}

void
end_screen(void)
{
    _displaycursor(_GCURSORON);

    _setvideomode(_DEFAULTMODE);
}
