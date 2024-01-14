#include<string.h>
#include<stdio.h>
#include"modules/parser.h"
#include"modules/lexer.h"
#include"modules/intopost.h"
#include"modules/interpretor.h"

#define INVALID_RESULT 1.22323425442431

int main(){
    while(1){
        string input;
        take_input(input);
        if(strcmp(input, "exit") == 0){
            break;
        }
        Tokens* tokens = returnTokens(input);
        if(!tokens){
            continue;
        }
        if(!isValidExpression(input)) 
            printf("The expression is mathematically wrong\n");
        
        Tokens* postfix = infixToPostfix(tokens);
        char* postfixExpression = returnPostfixExpression(postfix);
        double result = evaluatePostfix(postfixExpression);
        
        if(result == INVALID_RESULT){
            continue;
        }
      
        printf("%.2f\n", result);
    }
    return 0;
}
