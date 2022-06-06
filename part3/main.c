#include "skiplist.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    const int TEST_COUNT = 3;
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

int main(){
    if(0){
        skip_list l;
        l = start_list(4);
        dumb_test(l);
        print_list(l);
        search_list(l, 4);
        remove_list(l, 4);
        printf("Removed 4\n");
        remove_list(l, 9);
        printf("Removed 9\n");
        remove_list(l, 0);
        printf("Removed 0\n");
        free_list(l);
    } else {
        //printf("Testing by inserting 100k items, randomly ordered, 100 times\n");
        //printf("Depth 4:");
        //perf_test( 4);
        //printf("Depth 8:");
        perf_test( 8);
        //printf("Depth 16:");
        //perf_test(16);
    }
    return 0;
}
