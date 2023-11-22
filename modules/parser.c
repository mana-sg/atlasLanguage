#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "parser.h"

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->items = (char*)malloc(sizeof(char) * capacity);
    return stack;
}

void push(Stack* stack, char value) {
    stack->items[++stack->top] = value;
}

char pop(Stack* stack) {
    return stack->items[stack->top--];
}

char peek(Stack* stack) {
    return stack->items[stack->top];
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int isOpeningBracket(char ch) {
    return (ch == '(' || ch == '[' || ch == '{');
}

int isClosingBracket(char ch) {
    return (ch == ')' || ch == ']' || ch == '}');
}

int isValidExpression(const char* expression) {
    if(strlen(expression) <=2){
    return 0;
    }
    Stack* bracketStack = createStack(strlen(expression));

    for (int i = 0; i < strlen(expression); i++) {
        if (isOpeningBracket(expression[i])) {
            push(bracketStack, expression[i]);
        } else if (isClosingBracket(expression[i])) {
            if (bracketStack->top == -1 || 
                ((expression[i] == ')' && peek(bracketStack) != '(') ||
                 (expression[i] == ']' && peek(bracketStack) != '[') ||
                 (expression[i] == '}' && peek(bracketStack) != '{'))) {
                return 0;
            }
            pop(bracketStack);
        } else if (!isdigit(expression[i]) && !isOperator(expression[i])) {
            return 0;
        }
    }

    if (bracketStack->top != -1) {
        return 0;
    }

    for (int i = 0; i < strlen(expression) - 1; i++) {
        if (isOperator(expression[i]) && isOperator(expression[i + 1])) {
            return 0;
        }
    }

    return 1;
}
