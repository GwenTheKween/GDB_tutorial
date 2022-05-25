#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void usage(char* name){
    printf("Usage: %s <expression>\n", name);
    printf("\tPlease make sure that the expression is a single argument.\n\tYou probably need \" \" around the expression. \n");
}

void scream_and_die(const char* message){
    printf("%s\n", message);
    exit(1);
}

int has(char* expr, char c){
    while(*expr){
        if(*expr == c)
            return 1;
        if(*expr == ' ')
            return 0;
        expr++;
    }
    return 0;
}

int find_open_paren(char** sep, int end){
    char* expr = sep[end];
    int diff = 0;
    while(expr != sep[0]){
        if(*expr == '('){
            //found it!
            //TODO actual calculation
            return diff;
        }else if(*expr == ' ')
            diff ++;
    }
    scream_and_die("No opening parenthesis");
}

int priority(char c){
    if(isdigit(c) || c == '(' || c == ')')
        return 0;
    if(c == '-' || c == '+')
        return 1;
    if(c == '/' || c == '*')
        return 2;
    if(c == '^' || c == 's')
        return 3; //'s' is the start of "sqrt" expression
    scream_and_die("unknown start of expression");
}

int count_spaces(char* expr) {
    int n = 0;
    while(*expr) {
        if(*expr == ' ') n++;
        expr++;
    }
    return n;
}

void populate_separated(char* expr, char** sep){
    int i = 0;
    sep[i] = expr;
    i++;
    while(*expr){
        if(*expr == ' '){
            sep[i] = expr + 1;
            i++;
        }
        expr++;
    }
}

double solve(char** sep, int count) {
    int highest_priority = 0;
    for(int i = 1; i<count; i++){
        int curr_priority = priority(sep[i][0]);
        if(curr_priority > priority(sep[highest_priority][0])){
            highest_priority = i;
        }
    }
    //POSSIBLE BUG HERE ?
    if (priority(sep[highest_priority][0]) == 0)
        return atof(*sep);
    int left_ind = highest_priority - 1;
    int right_ind = highest_priority + 1;
    if(has(sep[left_ind], ')')){
        int left_start = find_open_paren(sep, left_ind);
    }
}

int main(int argc, char** argv){
    int len, spaces;
    char** separated;
    if(argc != 2){
        usage(argv[0]);
        return 0;
    }
    len = strlen(argv[1]);
    spaces = count_spaces(argv[1]);
    separated = (char**) malloc(sizeof(char*) * (spaces + 1));
    populate_separated(argv[1], separated);
    //solve(argv[1], len);
    printf("The solution to %s is: %lf\n", argv[1], solve(separated, spaces + 1));
    return 0;
}
