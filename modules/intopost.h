#ifndef INTOPOST_H
#define INTOPOST_H

typedef struct {
    int top;
    Tokens** array;
} StackTokens;

StackTokens* createStackToken();
Tokens* popToken(StackTokens* stack);
Tokens* infixToPostfix(Tokens* infixExpression);
void pushToken(StackTokens* stack, Tokens* item);
char* returnPostfixExpression(Tokens* postfixExpression);
int isEmptyTokens(StackTokens* stack);
int getPrecedence(char* operator);

#endif