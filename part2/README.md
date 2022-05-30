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


# Known bugs

* str_equal only checks to see if we're at the end of the first string
* do_substring doesn't check if we are only inside the string
* do_check_substring does not increase i when moving (better to use i+j)
* do_check_substring does not find if the substring is exactly the end of the string
* palindrome does not actually check the whole string. It only checks the first character with every other character

# Class structure

Start by talking about the program idea, run the base program, show something working. Then start working at the bugs

## str_equal

This will be used to show the commands 1(step), 4(display), 5(until); step into the function, run a few iterations with next and display, finish with until and show the problem

## substring

This will be used to show the commands 2 (break), 3(info break), and 6(finish)

## Palindrome

This shows the final commands, 7,8 and 9, mostly helpful with recursion.

check_substrings are there for extra practice
