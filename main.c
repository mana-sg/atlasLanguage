#include<stdio.h>
#include"modules/parser.h"
#include"modules/lexer.h"
#include"modules/intopost.h"
#include"modules/interpretor.h"

int main(){
    while(1){
        string input;
        take_input(input);
        Tokens* tokens = returnTokens(input);
        printf("The tokens list are: \n [ ");
        displayTokens(tokens);
        printf("]\n\n");
        if(isValidExpression(input))
            printf("The expression is mathematically correct\n");
        else{
            printf("The expression is mathematically wrong\n");
            return 0;
        }
        Tokens* postfix = infixToPostfix(tokens);
        char* postfixExpression = returnPostfixExpression(postfix);
        printf("Postfix expression: %s\n", postfixExpression);
        double result = evaluatePostfix(postfixExpression);
        printf("Result: %.2f\n", result);
    }
    return 0;
}