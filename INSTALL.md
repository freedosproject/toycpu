How to Compile Toy CPU
======================

Version 3
---------
The current version is 3.1 (Apr 13, 2023)

If you're trying to run the Version 3 of the Toy CPU, note that this
is a DOS program, so you need to run it under DOS. I use FreeDOS in a
virtual machine on Linux, but you can use DOSBox if you prefer.

There's already a DOS executable (EXE) available to download.

If you want to compile this yourself, you'll need the OpenWatcom C
compiler. If you're using FreeDOS, you can install this from the FreeDOS
LiveCD by running `FDIMPLES` and selecting the OpenWatcom C compiler.

Set up your DOS environment with OpenWatcom C using the `OWSETENV.BAT`
batch file, then do this:

1. Download the toycpu-3.1.zip source archive
2. Copy the zip file to your FreeDOS instance (I might save it as TOYCPU.ZIP so you can stay within the 8.3 filenames)
3. Extract the archive in FreeDOS with `unzip -j toycpu.zip -d toycpu` (the `-j` option says to "junk" the paths, and `-d` says to extract to the `toycpu` directory)
4. Go into the source directory with `cd toycpu`
5. Run the `build.bat` batch file

That should compile it for you. (Key step is to set up your OpenWatcom
C environment first.)


Version 2
---------

Before you try to compile, you'll need the ncurses libraries installed
on your system. For example, on a Fedora Linux system, use this command
to install the ncurses libraries:

```
$ sudo dnf install ncurses-devel
```

Then do this:

1. Download the toycpu-2.0.tar.gz source archive
2. Extract the archive with `tar xzf toycpu-2.0.tar.gz`
3. Go into the source directory with `cd toycpu-2.0`
4. Type `make`

That will compile the Toy CPU so you can run it:

```
$ make
gcc -DUSE_HELP -Wall -c toy.c
gcc -DUSE_HELP -Wall -c screen.c
gcc -DUSE_HELP -Wall -c cpu.c
gcc -DUSE_HELP -Wall -c input.c
gcc -DUSE_HELP -Wall -o toy toy.o screen.o cpu.o input.o -lncurses 
```

and:

```
$ ls
bit.h  cpuinstr.h  input.h  Makefile   screen.h  toy.c
cpu.c  cpu.o       input.o  README.md  screen.o  toy.o
cpu.h  input.c     LICENSE  screen.c   toy
```

Now you can run the Toy CPU by typing `./toy`
