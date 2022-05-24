CC = gcc
SOURCE = hello_world.c

simple:
	$(CC) $(SOURCE)                  -o hello

sym:
	$(CC) $(SOURCE) -g               -o symbols

opt:
	$(CC) $(SOURCE) -O0 -g           -o optimization

macro:
	# DWARF-4 SHOULD NOT BE NEEDED, THIS IS A KNOWN BUG
	# https://sourceware.org/bugzilla/show_bug.cgi?id=27306
	$(CC) $(SOURCE) -O0 -g3 -gdwarf-4 -o macros

fixed:
	$(CC) $(SOURCE) -O0 -g3 -DFOUR=4 -o fixed

all: simple sym opt macro
