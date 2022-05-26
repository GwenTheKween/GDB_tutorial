# Explanation

This is where explanations for the exercises are kept. Welcome!

Commands:
1. make: This is the base compilation command of all exercises. Makefiles run when this command is hit
2. make symbols: This will compile the source file with debugging symbols. it is the very minimum to have a minimally decent debugging session
3. make opt: This line will disable all optimizations, which makes you debugging MUCH better. GDB is quite unable to deal with optimizations.
4. make macros: This is the full compilation command I would usually suggest. -g3 will add information for macros, hence the name.
  4.1 Right now (GDB 12.1 on fedora 36) there is a bug where GDB can't deal with macros and DWARF-5, so we have to compile under dwarf-4. This should be done with soon(TM)
  
GDB stuff:
1. gdb -q: Runs gdb quietly. Blessed quietness and no copyright blurb
2. gdb -tui: Runs with the TUI interface. it show the file that is being debugged
3. (gdb) start: Starts the program, and stops at the first line of code in the main function.
4. (gdb) print <symbol>: print the given symbol, that can be a variable, a macro or a function (or more).

# Class flow

First, run GDB and talk shit about getting comfy with the huge copyright blurb. Then show the gdb -q wonder. Also show apropos and help, just in case

Now compile the program and show the source file with `gdb -q -tui` and show the wonders of a decent interface for gdb. But the basic `make` dont give symbols

Make symbols will show the thing. Show the difference, mention optimization, then say that there could be a problem with macros, so try to print and fail

Finally, show with macros, find the problem, use make fixed and yay, move on
