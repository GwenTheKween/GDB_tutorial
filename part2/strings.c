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
            s[size] = '\0';
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

void str_cp(char* to, char* from){
    while(*from){
        *to = *from;
        to++; from++;
    }
    *to = 0;
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

int str_len(char* str){
    int sz = 0;
    while(*str){
        str++;
        sz++;
    }
    return sz;
}

int to_int(char* c){
    int n = 0;
    while(*c){
        n *= 10;
        n += (*c - '0');
        c++;
    }
    return n;
}

void do_substring(){
    char *str, *number;
    int start, len;
    printf("Please enter the base string: ");
    str = le_string();

    printf("Please enter the starting index: ");
    number = le_string();
    start = to_int(number);
    free(number);

    printf("Please enter the size of the substring: ");
    number = le_string();
    len = to_int(number);
    free(number);

    printf("\nThe substring is: ");
    for(int i = 0; i < len; i++){
        printf("%c", str[i + start]);
    }
    printf("\n");
}

void do_compare(){
    char *str1, *str2;
    printf("Please enter the first string: ");
    str1 = le_string();
    printf("Please enter the second string: ");
    str2 = le_string();
    if(str_equal(str1, str2)){
        printf("The strings are equal\n");
    }else{
        printf("The strings are different\n");
    }
}

void do_check_substring(){
    char *str, *sub;
    printf("Please input the first (bigger) string: ");
    str = le_string();
    printf("Please input the second (smaller) string: ");
    sub = le_string();
    if(str_len(str) > str_len(sub)){
        int i, size1, size2, j;
        size1 = str_len(str);
        size2 = str_len(sub);
        for(i = 0; i < size1 - size2; i++){
            for(j = 0; j < size2; j++){
                if(str[i] != sub[j]) break;
            }
            if(j == size2){
                printf("the substring happens at least once!\n");
                return;
            }
        }
    }
    printf("\nIt is not a substring\n");
}

void do_get_size(){
    char* str;
    printf("Please input a string: ");
    str = le_string();
    printf("the given string has size %d\n", str_len(str));
    free(str);
}

int palindrome_recursive(char* str, int len){
    if(len < 3){
        //1-sized strings are always palindromes
        if(len == 1)
            return 1;
        //2-sized are palindromes if the first is the same as the last
        return str[0] == str[1];
    }
    // if the first and last are the same, we see if 
    // the internal string is a palindrome
    if(str[0] == str[len-1])
        return palindrome_recursive(str, len-2);
    //otherwise, it is not a palindrome
    return 0;
}

void do_palindrome(){
    char* str;
    int len;
    printf("Please enter the string to be tested: ");
    str = le_string();
    len = str_len(str);
    if(palindrome_recursive(str, len)){
        printf("It is a palindrome!\n");
    }else{
        printf("It is not a palindrome\n");
    }
}

int main(){
    char *option = NULL;
    printf("Please choose one option from the menu below:\n"
           "\tpalindrome\t: print if the given string is a palindrome\n"
           "\tsize\t\t: print the size of the given string\n"
           "\tequal\t\t: test if the 2 given strings are equal\n"
           "\tcontains\t: test if the small string is contained in the big one\n"
           "\tsubstring\t: return a substring of the given string\n"
           "\texit\t\t: leave the program\n");
    option = le_string();
    if(str_equal(option, "substring")){
        do_substring();
    } else if (str_equal(option, "equal")) {
        do_compare();
    } else if (str_equal(option, "contains")) {
        do_check_substring();
    }else if(str_equal(option, "size")) {
        do_get_size();
    }else if(str_equal(option, "palindrome")){
        do_palindrome();
    } else {
        printf("Unknown option\n");
    }
    free(option);
    return 0;
}
