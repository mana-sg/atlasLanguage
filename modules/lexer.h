#ifndef LEXER_H
#define LEXER_H

typedef char string[1000];

typedef struct token{
    char* type;
    int value;
} Token;

typedef struct tokens{
    Token *token;
    struct tokens *next;
} Tokens;

Tokens* returnTokens(string input);
Token* create_node(char *type, int value);
Token* getNextToken(string input, int *index);
void addToken(Tokens* tokens, Token *token);
void take_input(string command);
void displayTokens(Tokens* tokens);

#endif