#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

void take_input(string command){
    printf("<<Atlas>> ");
    scanf(" %[^\n]s", command);
}

Token* create_node(char *type, int value){
    Token *new_node = (Token*)malloc(sizeof(Token*));
    new_node->type = type;
    new_node->value = value;
    return new_node;
}

void addToken(Tokens* tokens, Token *token) {
    Tokens *new_node = (Tokens*)malloc(sizeof(Tokens*));
    new_node->token = token;
    new_node->next = NULL;
    while(tokens->next){
        tokens = tokens->next;
    }
    tokens->next = new_node;
}

Token* getNextToken(string input, int *index) {
    while(input[*index] == ' ') {
        (*index)++;
    }

    if (input[*index] == '\0') {
        return create_node("END", 0);
    }

    if ((input[*index] >= '0') && (input[*index] <= '9')) {
        int value = 0;
        while (((input[*index]) >= '0') && ((input[*index]) <= '9')) {
            value = value * 10 + (input[*index] - '0');
            (*index)++;
        }
        return create_node("NUMBER", value);
    }

    char op = input[*index];
    (*index)++;
    switch (op) {
        case '+': return create_node("PLUS", 0);
        case '-': return create_node("MINUS", 0);
        case '*': return create_node("MUL", 0);
        case '/': return create_node("DIVIDE", 0);
        case '(': return create_node("LPAREN", 0);
        case ')': return create_node("RPAREN", 0);
        default:
            printf("Error: Invalid character '%c'\n", op);
            exit(0);
    }
}

void displayTokens(Tokens* tokens){
    while(tokens){
        printf("%s ", tokens->token->type);
        tokens = tokens->next;
    }
}

Tokens* returnTokens(string input){
    Tokens* tokens_list = (Tokens*)malloc(sizeof(Tokens*));
    Token* token = (Token*)malloc(sizeof(Token*));;
    int index = 0;
    tokens_list->next = NULL;
    tokens_list->token = getNextToken(input, &index);
    while(input[index] != '\0'){
        token = getNextToken(input, &index);
        addToken(tokens_list, token);
        }
    return tokens_list;
}
