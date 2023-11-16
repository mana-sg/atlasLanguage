#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char string[1000];

typedef struct token{
    char* type;
    int value;
} Token;

typedef struct tokens{
    Token *token;
    struct tokens *next;
} Tokens;


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

///////////////////////////////////////////
//LEXER
//////////////////////////////////////////
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
        return create_node("INTEGER", value);
    }

    char op = input[*index];
    (*index)++;
    switch (op) {
        case '+': return create_node("PLUS", 0);
        case '-': return create_node("MINUS", 0);
        case '*': return create_node("MULTIPLY", 0);
        case '/': return create_node("DIVIDE", 0);
        case '(': return create_node("LPARENTHESIS", 0);
        case ')': return create_node("RPARENTHESIS", 0);
        default:
            printf("Error: Invalid character '%c'\n", op);
            exit(0);
    }
}
///////////////////////////////////////////
//LEXER
//////////////////////////////////////////

void display(Tokens* tokens){
    while(tokens){
        printf("%s ", tokens->token->type);
        tokens = tokens->next;
    }
}

int main() {
    while(1){
        string input;
        int index = 0;
        take_input(input);
        Token *token;
        Tokens *tokens = (Tokens*)malloc(sizeof(Tokens*));
        tokens->next = NULL;
        tokens->token = getNextToken(input, &index);
        while(input[index] != '\0'){
            token = getNextToken(input, &index);
            addToken(tokens, token);
        }
        display(tokens);
        printf("\n");

    }

    return 0;
}
