#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "interpretor.h"

void initialize(StackEvaluate* stack) {
    stack->top = -1;
}

int isEmptyEvaluate(StackEvaluate* stack) {
    return stack->top == -1;
}

void pushEvaluate(StackEvaluate* stack, double value) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->items[++stack->top] = value;
}

double popEvaluate(StackEvaluate* stack) {
    if (isEmptyEvaluate(stack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->items[stack->top--];
}

double evaluatePostfix(char* expression) {
    StackEvaluate stack;
    initialize(&stack);

    for (int i = 0; expression[i] != '\0'; ++i) {
        if (isdigit(expression[i])) {
            double number = 0;
            while (isdigit(expression[i])) {
                number = number * 10 + (expression[i] - '0');
                ++i;
            }
            --i;
            pushEvaluate(&stack, number);
        } else if (expression[i] == ' ') {
            continue;
        } else {
            double operand2 = popEvaluate(&stack);
            double operand1 = popEvaluate(&stack);

            switch (expression[i]) {
                case '+':
                    pushEvaluate(&stack, operand1 + operand2);
                    break;
                case '-':
                    pushEvaluate(&stack, operand1 - operand2);
                    break;
                case '*':
                    pushEvaluate(&stack, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 != 0) {
                        pushEvaluate(&stack, operand1 / operand2);
                    } else {
                        printf("Error: Division by zero\n");
                        return 1.22323425442431;
                    }
                    break;
                default:
                    printf("Error: Invalid operator\n");
                    return 1.22323425442431;
            }
        }
    }

    if (!isEmptyEvaluate(&stack) && stack.top == 0) {
        return popEvaluate(&stack);
    } else {
        printf("Error: Invalid postfix expression\n");
        exit(EXIT_FAILURE);
    }
}
