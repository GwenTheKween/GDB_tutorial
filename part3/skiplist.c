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

static void free_no(no n){
    memset(n, 0, sizeof(struct list_no));
    free(n);
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

static void remove_no(no n){
    no prev = n->left;
    no next = n->right;
    if(prev){
        prev -> right = n -> right;
    }
    if(next) {
        next -> left = n -> left;
    }
    free_no(n);
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
    if(n -> val > num && n->left){
        if(verbose) printf("backing once\n");
        n = n ->left;
    }

    if(n -> down != NULL){
        if(verbose) printf("moving down\n");
        return _list_search(n->down, num, verbose);
    }
    /* We're at the lowest list, so either we found it, or it doesn't exist. */
    return n;
}

/* Move the top of the head tower to the second element of the list,
   and return the highest node that didn't need to be moved.  */
static no _move_head(no n){
    no bottom = n;
    /* Find the second number of the list.  */
    while(bottom -> down) bottom = bottom ->down;
    no second = bottom -> right;

    /* Find the highest element of the second node of list.  */
    while(second -> up){
        bottom = bottom -> up;
        second = second -> up;
    }

    /* Move all remaining nodes from the head.  */
    /* first the quick exit, if we need to move nothing.  */
    if (bottom == n) return n;
    /* If we didn't take the quick exit, bottom has at least one up node.  */
    n = bottom;
    bottom = bottom -> up;
    /* Move the node to be above the second, and change the value.  */
    while(bottom->down) {
        second -> up = bottom;
        bottom -> down = second;
        bottom -> val = second -> val;
        second = bottom;
        bottom = bottom -> up;
    }
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
    while(m && n){
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
    if(n -> val > num){
        /* This means that we are inserting in the first slot, so make
           a new head.  */
        if(n->left == NULL){
            insert_head(l, num);
            return 1;
        }
        no to_ins = create_no(num);
        insert_before(n, to_ins);
        maybe_insert_up (to_ins, l->depth - 1);
    } else {
        no to_ins = create_no(num);
        insert_after(n, to_ins);
        maybe_insert_up (to_ins, l->depth - 1);
    }
    return 1;
}

int search_list(skip_list l, int num){
    return _list_search(l->head, num, 0) != NULL;
}

static void _remove_head(skip_list l){
    no bottom = _move_head(l->head);

    /* Free the tower.  */
    while(bottom -> down){
        bottom = bottom -> down;
        free_no(bottom -> up);
    }
    free_no(bottom);
}

/* Returns 1 if the element was removed, 0 if not.  */
int remove_list(skip_list l, int num){
    if(l->head->val == num){
        _remove_head(l);
        return 1;
    }
    no n = _list_search(l->head, num, 0);
    if(n == NULL) return 0; /* Nothing to remove.  */


    while(n -> down){
        n = n->down;
        remove_no(n->up);
    }
    remove_no(n);
    return 1;
}

void print_list(skip_list l){
    int mx = l->depth;
    no n = l->head;
    /* We have to print from the bottom to see all elements.  */
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

static void free_level(no start){
    no n = start;
    while(n -> right){
        n = n->right;
        free_no(n->left);
    }
    free_no(n);
}

void free_list(skip_list l){
    no n = l->head;
    while(n->down){
        n = n -> down;
        free_level(n -> up);
    }
    free_level(n);
    free(l);
}
