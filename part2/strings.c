#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define INCR 10

char* le_string(){
    char* s;
    int mx = INCR, size = 0;
    char c;
    s = (char*) malloc(sizeof(char) * mx);
    while(1){
        c = getchar();
        if(c == '\n'){
            /* BUG ON PURPOSE HERE */
            //s[size] = '\0';
            break;
        }else{
            s[size] = c;
            size++;
            if(size >= mx){
                char* tmp;
                tmp = realloc(s, mx + INCR);
                if(tmp == NULL){
                    printf("REALLOC FAIL. this was not an expected bug\n");
                    exit(ENOMEM);
                }
                s = tmp;
                mx += INCR;
            }
        }
    }
    return s;
}

int str_equal(char* a, char* b){
    while(*a && *b && (*a == *b)){
        a++;
        b++;
    }
    /* BUG ON PURPOSE HERE! */
    if(*a == '\0') return 1;
    return 0;
}

int string_len(char* str){
    int sz = 0;
    while(*str){
        str++;
        sz++;
    }
    return sz;
}

void do_substring(){
}

void do_compare(){
}

void do_check_substring(){
}

void do_get_size(){
    char* str;
    printf("Please input a string: ");
    str = le_string();
    printf("the given string has size %d\n", string_len(str));
    free(str);
}

int main(){
    char *option = NULL;
    printf("Please choose one option from the menu below:\n"
           "\tsize\t\t: print the size of the given string\n"
           "\tequal\t\t: test if the 2 given strings are equal\n"
           "\tcontains\t: test if the second given string is contained in the string\n"
           "\tsubstring\t: return a substring of the given string\n"
           "\texit\t\t: leave the program\n");
    option = le_string();
    while(!str_equal(option, "exit")){
        if(str_equal(option, "substring")){
            do_substring();
        } else if (str_equal(option, "equal")) {
            do_compare();
        } else if (str_equal(option, "contains")) {
            do_check_substring();
        }else if(str_equal(option, "size")) {
            do_get_size();
        } else {
            printf("Unknown option\n");
        }
        free(option);
        option = le_string();
    }
    return 0;
}
