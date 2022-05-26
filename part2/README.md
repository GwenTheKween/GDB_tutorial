# Explanation

GDB stuff:
1. (gdb) step: Go to the next line, or enter the function in the current line.
2. (gdb) break <location>: add a "breakpoint" instruction at the given location. Once the Inferior hits the breakpoint, the inferior will stop and GDB will report to the user that the breakpoint was hit
3. (gdb) info break: Lists all active breakpoints
4. (gdb) display: show a variable after any step is taken.
5. (gdb) until [<line>]: keep executing until the given line is reached, or next line if no line is given
6. (gdb) finish: run until the end of the current function
7. (gdb) backtrace [<count>]: See the call stack of the program, or "how did I get here". If count is given, shows only <count> stacks
8. (gdb) up [<count>] and (gdb) down [<count>]: move up and down the callstack, to check "why did I get here"?
9. (gdb) info locals: Show all variables in the current frame, so you know "what is going on here".
