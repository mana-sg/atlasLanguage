#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "intopost.h"


// Function to create a StackTokens
StackTokens* createStackToken() {
    StackTokens* stack = (StackTokens*)malloc(sizeof(StackTokens));
    stack->top = -1;
    stack->array = (Tokens**)malloc(sizeof(Tokens*));
    return stack;
}

// Function to check if the stack is empty
int isEmptyTokens(StackTokens* stack) {
    return stack->top == -1;
}

// Function to pushToken an element onto the stack
void pushToken(StackTokens* stack, Tokens* item) {
    stack->top++;
    stack->array = (Tokens**)realloc(stack->array, (stack->top + 1) * sizeof(Tokens*));
    stack->array[stack->top] = item;
}

// Function to popToken an element from the stack
Tokens* popToken(StackTokens* stack) {
    if (!isEmptyTokens(stack)) {
        return stack->array[stack->top--];
    }
    return NULL; // Invalid value for an empty stack
}

int getPrecedence(char* operator) {
    if (strcmp(operator, "PLUS") == 0 || strcmp(operator, "MINUS") == 0) {
        return 1;
    } else if (strcmp(operator, "MUL") == 0 || strcmp(operator, "DIVIDE") == 0) {
        return 2;
    }
    return 0; 
}

Tokens* infixToPostfix(Tokens* infixExpression) {
    Tokens* postfixHead = NULL;
    Tokens* postfixTail = NULL;

    StackTokens* stack = createStackToken();

    while (infixExpression != NULL) {
        Token* currentToken = infixExpression->token;

        if (strcmp(currentToken->type, "NUMBER") == 0) {
            Tokens* newTokens = (Tokens*)malloc(sizeof(Tokens));
            newTokens->token = currentToken;
            newTokens->next = NULL;

            if (postfixHead == NULL) {
                postfixHead = postfixTail = newTokens;
            } else {
                postfixTail->next = newTokens;
                postfixTail = newTokens;
            }
        } else if (strcmp(currentToken->type, "LPAREN") == 0) {
            pushToken(stack, infixExpression);
        } else if (strcmp(currentToken->type, "RPAREN") == 0) {
            while (!isEmptyTokens(stack) && strcmp(stack->array[stack->top]->token->type, "LPAREN") != 0) {
                Tokens* popTokenpedTokens = popToken(stack);
                if (postfixHead == NULL) {
                    postfixHead = postfixTail = popTokenpedTokens;
                } else {
                    postfixTail->next = popTokenpedTokens;
                    postfixTail = popTokenpedTokens;
                }
            }
            popToken(stack); // popToken '(' Tokens from the stack
        } else { // Operator
            while (!isEmptyTokens(stack) && getPrecedence(stack->array[stack->top]->token->type) >= getPrecedence(currentToken->type)) {
                Tokens* poppedTokens = popToken(stack);
                if (postfixHead == NULL) {
                    postfixHead = postfixTail = poppedTokens;
                } else {
                    postfixTail->next = poppedTokens;
                    postfixTail = poppedTokens;
                }
            }

            Tokens* newTokens = (Tokens*)malloc(sizeof(Tokens));
            newTokens->token = currentToken;
            newTokens->next = NULL;

            pushToken(stack, newTokens);
        }

        infixExpression = infixExpression->next;
    }

    while (!isEmptyTokens(stack)) {
        Tokens* popTokenpedTokens = popToken(stack);
        if (postfixHead == NULL) {
            postfixHead = postfixTail = popTokenpedTokens;
        } else {
            postfixTail->next = popTokenpedTokens;
            postfixTail = popTokenpedTokens;
        }
    }

    return postfixHead;
}

char* returnPostfixExpression(Tokens* tokensList) {
    Tokens* current = tokensList;

    // Calculate the total length needed for the string
    int totalLength = 0;
    while (current != NULL) {
        totalLength += snprintf(NULL, 0, "%d ", current->token->value);
        current = current->next;
    }

    // Allocate memory for the string
    char* resultString = (char*)malloc(totalLength + 1);

    // Concatenate token values into the string
    current = tokensList;
    int currentIndex = 0;
    while (current != NULL) {
        if(strcmp(current->token->type,"NUMBER") == 0){
            currentIndex += snprintf(resultString + currentIndex, totalLength - currentIndex + 1, "%d ", current->token->value);
        }
        else{
            char operatorConcat;
            if(strcmp(current->token->type, "PLUS") == 0){
                operatorConcat = '+';
            }
            else if(strcmp(current->token->type, "MUL") == 0){
                operatorConcat = '*';
            }
            else if(strcmp(current->token->type, "MINUS") == 0){
                operatorConcat = '-';
            }
            else if(strcmp(current->token->type, "DIVIDE") == 0){
                operatorConcat = '/';
            }
            currentIndex += snprintf(resultString + currentIndex, totalLength - currentIndex + 1, "%c ", operatorConcat);
        }
        current = current->next;
    }

    return resultString;
}