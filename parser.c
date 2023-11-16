#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char operator;
    int value;
    struct Node* left;
    struct Node* right;
} Node;


Node* createNode(char operator, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->operator = operator;
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}


Node* parseExpression(char** tokens, int tokenCount) {
    Node* stack[tokenCount];
    int stackSize = 0;

    for (int i = 0; i < tokenCount; i++) {
        char* token = tokens[i];

        if (isdigit(token[0])) {
            stack[stackSize++] = createNode(' ', atoi(token));
        } else if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/') {
            if (stackSize < 2) {
                printf("Invalid expression\n");
                exit(1);
            }
            Node* right = stack[--stackSize];
            Node* left = stack[--stackSize];

            Node* operatorNode = createNode(token[0], 0);
            operatorNode->left = left;
            operatorNode->right = right;

            stack[stackSize++] = operatorNode;
        } else {
            printf("Invalid token: %s\n", token);
            exit(1);
        }
    }

    if (stackSize != 1) {
        printf("Invalid expression\n");
        exit(1);
    }

    return stack[0];
}
 
int evaluateExpression(Node* root) {
    if (root) {
        if (root->operator == ' ') {
            return root->value;
        } else {
            int left = evaluateExpression(root->left);
            int right = evaluateExpression(root->right);

            if (root->operator == '+') {
                return left + right;
            } else if (root->operator == '-') {
                return left - right;
            } else if (root->operator == '*') {
                return left * right;
            } else if (root->operator == '/') {
                if (right != 0) {
                    return left / right;
                } else {
                    printf("Division by zero\n");
                    exit(1);
                }
            }
        }
    }
    return 0;
}


void printAST(Node* root) {
    if (root) {
        printAST(root->left);
        if (root->operator == ' ') {
            printf("%d ", root->value);
        } else {
            printf("%c ", root->operator);
        }
        printAST(root->right);
    }
}

int main() {
    char* expression_list[] = {"3", "4", "*", "2", "5", "*", "+", "6", "-"};

    int tokenCount = sizeof(expression_list) / sizeof(expression_list[0]);
    Node* ast = parseExpression(expression_list, tokenCount);

    
    printf("Expression in infix notation: ");
    printAST(ast);
    printf("\n");

 
    int result = evaluateExpression(ast);
    printf("Result of the expression: %d\n", result);

return 0;
}