.PHONY: all clean realclean distclean

SRC=toy.c screen.c cpu.c input.c
OBJ=$(SRC:.c=.o)

CC=gcc
CPPFLAGS=-DUSE_HELP
CFLAGS=-Wall
LDLIBS=-lncurses
LDFLAGS=
RM=/bin/rm -f -v

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

all: toy

toy: $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o toy $(OBJ) $(LDLIBS) $(LDFLAGS)

clean:
	-$(RM) *~

realclean: clean
	-$(RM) *.o

distclean: realclean
	-$(RM) toy
