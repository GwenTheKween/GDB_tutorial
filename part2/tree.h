#include <stdio.h>
#include <vector>
#include <string>

enum OPERATION{
    NONE,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};

OPERATION which_operation(char c){
    if(c == '+')
        return ADD;
    if(c == '-')
        return SUB;
    if(c == '*')
        return MULTIPLY;
    if(c == '/')
        return DIVIDE;
    return NONE;
}

class no{
private:
    no* parent;
    no *left, *right;
    OPERATION op;
    double value;
public:
    no(no* p, char* expr):
        parent(p), left(nullptr), right(nullptr)
        {
        op = which_operation(*expr);
        if(op == NONE){
            value = atof(expr);
        }else{
            value = 0;
        }
    }
}

std::vector<std::string> tokenize(char* expr){
    std::vector<std::string> tokens;
    std::string s(expr);
    for(int i=0; i!=string::npos;){
        int j = s.find(' ');
        int k = s.find('(');
        if(k != string::npos){
            //there are open parenthesis somewhere.
            //parenthesized expressions are a single token
            //so lets see if the space we found is after the parenthesis:
            if(k < j){
                //it is, so we need the first space after the parenthesis
                //instead
                j = s.find(' ', s.find(')'));
                //We dont care if j == npos at this point
            }
        }
        if(j != string::npos)
            tokens.push_back(s.substr(i,j-i));
        else
            tokens.push_back(s.substr(i));
        i = j;
    }
    return tokens;
}

class expression{
private:
    no* root;
    char* str;
public:
    expression(char* expr){
        str = expr;
        std::vector<std::string> tokens = tokenize(expr);
        root = create_subtree(tokens);
    }
    no* create_subtree(std::vector<std::string> tokens){
        no* root;
        //first: Find top-level operation
        //this would be the the first operation with the
        //highest priority we can find.
        //
        //Then: recursively create nodes (another function)
        //to the left and right.  If a node would be created
        //on a parenthesized token we instead create a subtree,
        //recursively callling this function.
    }
}
