#include "skiplist.h"

int main(){
    skip_list l;
    //l = start_list(1);
    l = start_list(4);
    dumb_test(l);
    print_list(l);
    search_list(l, 4);
    free_list(l);
    return 0;
}
