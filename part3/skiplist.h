#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

typedef struct skipList* skip_list;

skip_list start_list(int);
void print_list(skip_list);

void dumb_test(skip_list);

void free_list(skip_list);

#endif
