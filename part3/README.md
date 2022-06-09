# Explanation

This is an implementation of a skip list (https://en.wikipedia.org/wiki/Skip_list ). It's a not-quite-complete one, though. It can't have the max size dynamically based on the amount of elements or randomness, and it has some bugs on removing elements.

But that is for later, not for the start of the class. For the start we can see a few known bugs.

# GDB stuff

1. Pretty Printers - print variables in a custom way
2. Custom Commands - make GDB do a bunch of things in sequence, for convenience
3. Watchpoints, and watchpoint -l - Ask GDB to warn you when a bit of memory is changed.
4. list - show code arond where you are.
5. dprintf - print information when parts of the inferior are hit
6. cli --args - runs inferior with the exact given line
7. checkpoint - restart the inferior from this point

# Known bugs

* _list_search may return a non-NULL pointer even when the value is not found.
* _move_head doesn't change all pointers related to the head of the list.
* _remove_head doesn't change the head of the list.
* remove_list final while moves in the wrong direction.
* print_list uses the top, not bottom.

# Class structure

Show the image, show a working print (also in the presentation). Then, "lets see a working example", create a list with depth greater than 1, insert anything and print it, and the first bug is already apparent!

## print_list

This can be used to show pretty printers and custom commands. It is probably also useful to show --args, -ex and a .gdbinit

## _move_head

After fixing print_list, move on to inserting a number, then inserting a new number as the list head. Probably good to insert a couple of numbers before and after, though.

This can show watchpoints.
