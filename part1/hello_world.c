#include <stdio.h>
#include "obscure.h"

int main(){
    int x;
    x = THREE * FOUR;
    while(x--) {
        printf("Hello world!\n");
    }
    return x;
}
