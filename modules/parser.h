#ifndef PARSER_H
#define PARSER_H

typedef struct {
    char *items;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity);
void push(Stack* stack, char value);
char pop(Stack* stack);
char peek(Stack* stack);
int isOperator(char ch);
int isOpeningBracket(char ch);
int isClosingBracket(char ch);
int isValidExpression(const char* expression);

#endif