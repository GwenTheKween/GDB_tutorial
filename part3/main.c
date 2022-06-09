#include "skiplist.h"
#include <stdio.h>
#include <stdlib.h>

void shuffle(int *v, int size){
    /* shuffle from once to 3x the size of the array.  */
    int c = (rand()%3 + 1);
    for(int i = 0; i < c * size; i++){
        /* select the indices to be swapped.  */
        int x = rand() % size;
        int y;
        do{
            y = rand() % size;
        }while(x == y);

        /* Swap them.  */
        int tmp = v[x];
        v[x] = v[y];
        v[y] = tmp;
    }
}

#include <sys/time.h>
void perf_test(int depth){
    const int TEST_SIZE=10000;
    const int TEST_COUNT = 10;
    double total[] = {
        0, /* insertion time.  */
        0, /* search time.  */
        0, /* remove time.  */
    };
    int *v;
    v = (int *) malloc(sizeof(int) * TEST_SIZE);
    for(int i = 0; i < TEST_COUNT; i++){
        /* Reset array.  */
        for(int i = 0; i < TEST_SIZE; i++){
            v[i] = 3 * i;
        }
        /* shuffle array.  */
        shuffle(v, TEST_SIZE);

        /* start insertion test.  */
        struct timeval start, end;
        skip_list l;
        gettimeofday(&start, NULL);
        l = start_list(depth);
        for(int i = 0; i < TEST_SIZE; i++){
            insert_list(l, v[i]);
        }
        gettimeofday(&end, NULL);
        double temp = end.tv_usec - start.tv_usec;
        total[0] += (end.tv_sec - start.tv_sec) + temp/1000000;
        printf("finished %dth insert test\n", i+1);

        /* start search test.  */
        gettimeofday(&start, NULL);
        for(int i = 0; i < TEST_SIZE; i++){
            search_list(l, rand() % (3 * TEST_SIZE));
        }
        gettimeofday(&end, NULL);
        temp = end.tv_usec - start.tv_usec;
        total[1] += (end.tv_sec - start.tv_sec) + temp/1000000;
        printf("finished %dth search test\n", i+1);

        /* start remove test.  */
        gettimeofday(&start, NULL);
        for(int i = 0; i < TEST_SIZE; i++){
            remove_list(l, 3 * (rand() % TEST_SIZE));
        }
        gettimeofday(&end, NULL);
        temp = end.tv_usec - start.tv_usec;
        total[2] += (end.tv_sec - start.tv_sec) + temp/1000000;
        printf("finished %dth remove test\n", i+1);
        /* finish test.  */
        free_list(l);
        //fprintf(stderr,"Test %d done\n", i+1);
    }
    free(v);
    printf("The average time for insertion was %lf seconds\n"
           "The average time for searching was %lf seconds\n"
           "The average time for removing  was %lf seconds\n",
           total[0] / TEST_COUNT, total[1] / TEST_COUNT,
           total[2] / TEST_COUNT);
}

//===========================================================================================================

int menu(){
    int n;
    printf("Welcome to the testing grounds of the skip list.\n"
           "Please select the desired option:\n"
           "\t0. Exit\n"
           "\t1. Start a new list\n"
           "\t2. Insert an element to the list\n"
           "\t3. Search for an element on the list\n"
           "\t4. Remove an element from the list\n"
           "\t5. Print the list\n");
    scanf("%d", &n);
    return n;
}

int main(int argc, char** argv){
    int opt;
    if(argc == 2){
        opt = atoi(argv[1]);
    } else{
        opt = 0;
    }

    if(opt == 1){
        printf("Testing by inserting 10k items, randomly ordered, 10 times\n");
        printf("Depth 4:");
        perf_test( 4);
        printf("Depth 8:");
        perf_test( 8);
        printf("Depth 16:");
        perf_test(16);
    } else if (opt == 0){
        skip_list l = NULL;
        while(!opt){
            opt = menu();
            if(opt == 1){
                int d;
                printf("Please enter the depth of the skiplist:\n");
                scanf("%d", &d);
                if(l != NULL) free_list(l);
                l = start_list(d);
            } else if (opt == 2) {
                int elm;
                printf("Please enter the value to be inserted:\n");
                scanf("%d", &elm);
                elm = insert_list(l, elm);
                if(elm > 0) printf("insert ok\n");
                else if(elm == 0) printf("insert failed: element already exists\n");
                else printf("insert failed: unknown error (NOT a planned bug)\n");
            }else if(opt == 3){
                int elm;
                printf("Please enter element to be searched:\n");
                scanf("%d", &elm);
                printf("The searched element is%s in the list\n", (search_list(l, elm))?"":" not");
            }else if(opt == 4){
                int elm;
                printf("Please enter the element to be removed:\n");
                scanf("%d", &elm);
                if(remove_list(l, elm)) printf("Removal successful!\n");
                else printf("Removal failed. Likely not in the list\n");
            }else if(opt == 5){
                print_list(l);
            }
            opt = !opt;
        }
    }
    return 0;
}
