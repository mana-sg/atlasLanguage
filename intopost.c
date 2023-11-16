#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Stack structure for operators
typedef struct {
    int top;
    unsigned capacity;
    char *array;
} Stack;

// Initialize a stack
Stack *createStack(unsigned capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char *)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Check if the stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Push an element onto the stack
void push(Stack *stack, char op) {
    stack->array[++stack->top] = op;
}

// Pop an element from the stack
char pop(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top--];
    }
    return '\0'; // Empty stack marker
}

// Get the top element of the stack without popping
char peek(Stack *stack) {
    return stack->array[stack->top];
}

// Check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Get the precedence of an operator
int getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0; // For non-operators
}

// Convert infix expression to postfix
char *infixToPostfix(char *infix) {
    Stack *stack = createStack(strlen(infix));
    char *postfix = (char *)malloc((2 * strlen(infix) + 1) * sizeof(char));
    int i, j;
    i = j = 0;

    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' '; // Add a space to separate operands
        } else if (isOperator(infix[i])) {
            while (!isEmpty(stack) && getPrecedence(infix[i]) <= getPrecedence(peek(stack))) {
                postfix[j++] = pop(stack);
                postfix[j++] = ' '; // Add a space to separate operators
            }
            push(stack, infix[i++]);
        } else if (infix[i] == '(') {
            push(stack, infix[i++]);
        } else if (infix[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[j++] = pop(stack);
                postfix[j++] = ' '; // Add a space to separate operators
            }
            if (!isEmpty(stack) && peek(stack) == '(') {
                pop(stack);
            }
            i++;
        } else {
            i++; // Skip other characters
        }
    }

    while (!isEmpty(stack)) {
        postfix[j++] = pop(stack);
        postfix[j++] = ' '; // Add a space to separate operators
    }

    postfix[j] = '\0';
    return postfix;
}

int main() {
    char infix[100];
    printf("Enter the infix expression: ");
    scanf("%s", infix);

    char *postfix = infixToPostfix(infix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}