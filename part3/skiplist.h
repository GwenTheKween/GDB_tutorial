#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

typedef struct skipList* skip_list;

skip_list start_list(int);
void print_list(skip_list);
int insert_list(skip_list, int);
int search_list(skip_list, int);
int remove_list(skip_list, int);

void dumb_test(skip_list);

void free_list(skip_list);

#endif
