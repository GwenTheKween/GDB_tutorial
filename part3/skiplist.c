#include "skiplist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list_no{
    struct list_no *left, *right, *up, *down;
    int val;
};

typedef struct list_no* no;

static no create_no(int val){
    no n;
    n = malloc(sizeof(struct list_no));
    memset(n, 0, sizeof(struct list_no));
    n -> val = val;
    return n;
}

static void insert_before(no a, no b){
    /* sanity check.  */
    if(a == NULL || b == NULL) return;

    no prio = a->left;
    if(prio != NULL) prio -> right = b;
    b -> left = prio;
    a -> left = b;
    b -> right = a;
}

static void insert_after(no a, no b){
    /* sanity check.  */
    if(a == NULL || b == NULL) return;

    no next = a->right;
    if(next != NULL) next -> left = b;
    b -> right = next;
    a -> right = b;
    b -> left = a;
}

static void maybe_insert_up (no n, int mx){
    while(mx > 0) {
        if(rand() % 100 > 50){
            mx --;
            n -> up = create_no(n -> val);
            n -> up -> down = n;
            /* We will never try to insert up from the head.  */
            no m = n->left;
            /* Since the first is guaranteed to move up, we dont have to
               worry about m->left.  */
            while(!m->up){
                m = m->left;
            }
            n = n->up;
            m = m->up;
            insert_after(m, n);
        }else break;
    }
}

//==============================================================

struct skipList {
    no head;
    int depth;
};

/* This is an internal function that returns a pointer to the element, if 
   found, or the first element greater than num.  */
static no _list_search(no start, int num, int verbose){
    no n = start;

    /* This happens when the list is empty.  */
    if(n == NULL) return NULL;

    /* We only want to return the last level, so if the value was found, we'll
       continue the recursive calls down until we reach the last level. */
    if (start -> val == num) {
        if(verbose) printf("moving down\n");
        if(start -> down) return _list_search(start->down, num, verbose);
        return start;
    }
    /* Because the skiplist is ordered, we keep going to the next value until
       the current value is not smaller than what we're searching. */
    while(n ->right && (num > n -> val)){
        n = n->right;
        if(verbose) printf("moving right\n");
    }

    //There is a fun bug here. I can fix it for further buggage later

    if(n -> down != NULL){
        if(verbose) printf("moving down\n");
        return _list_search(n->down, num, verbose);
    }
    /* We're at the lowest list, so either we found it, or it doesn't exist. */
    return n;
}

skip_list start_list(int depth){
    skip_list l;
    l = malloc(sizeof(struct skipList));
    l -> head = NULL;
    l -> depth = depth;
    return l;
}

static void insert_head(skip_list l, int num){
    no n = l->head, m;
    l->head = create_no(num);
    m = l->head;
    /* First create the pile of members at the start of the list.  */
    for(int i = 1; i < l -> depth; i++, m = m->down){
        m -> down = create_no (num);
        m -> down -> up = m;
    }
    if (n == NULL) /* This was inserting the first element. We are done now.  */
        return;
    /* We need to link the new first item tower to the former tower.
       It is guaranteed that the former tower is as big as this one.  */
    m = l->head;
    while(m && n && m->down && n -> down){
        m->right = n;
        n-> left = m;
        m = m->down;
        n = n->down;
    }
}

/* Insert NUM into the skip_list L.  Returns: 
   1 if the insertion worked;
   0 if the value was already there;
   -1 if something else happened.  */
int insert_list(skip_list l, int num){
    no n;
    n = _list_search(l->head, num, 0);
    if(n == NULL){
        /* first insertion.  */
        insert_head(l, num);
        return 1;
    }
    if(n -> val == num) return 0;
    /* this is how I expect most insertions to go */
    no to_ins = create_no(num);
    if(n -> val > num){
        insert_before(n, to_ins);
    } else {
        /* This happens when we are inserting in the first slot */
        insert_after(n, to_ins);
    }
    maybe_insert_up (to_ins, l->depth - 1);
    return 1;
}

int search_list(skip_list l, int num){
    return _list_search(l->head, num, 1) != NULL;
}

void print_list(skip_list l){
    int mx = l->depth;
    no n = l->head;
    /* We have to print from the bottom to see all elements.  */
    //TODO remove this for a fun bug
    while(n->down) n = n->down;
    for(; n; n = n->right){
        no m = n;
        for(int i = 0; i < mx; i++){
            if(i) printf("<--->");
            if(m) printf("(%3d)",m->val);
            else  printf("  |  ");
            if(m) m = m -> up;
        }
        printf("\n  ");
        for(int j = 0; j < mx; j++) printf("|         ");
        printf("\n  ");
        for(int j = 0; j < mx; j++) printf("v         ");
        printf("\n");
    }
    for(int i = 0; i < mx; i++){
        if(i > 0) printf(" --- ");
        printf("(nil)");
    }
    printf("\n");
}

void dumb_test(skip_list l){
    for(int i = 0; i<10; i++){
        insert_list(l, i);
    }
}

void free_list(skip_list l){
    free(l);
}
