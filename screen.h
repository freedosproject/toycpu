#if !defined(SCREEN_H)
#define SCREEN_H

void
print_title(const char *title);

void
print_message(const char *message);

void
pause(const char *msg);

int
init_screen();

#define end_screen() (_setvideomode(_DEFAULTMODE))

#endif
