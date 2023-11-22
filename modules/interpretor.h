#ifndef INTERPRETOR_H
#define INTERPRETOR_H
#define MAX_SIZE 1000

typedef struct {
    int top;
    double items[MAX_SIZE];
} StackEvaluate;

double evaluatePostfix(char* expression);
double popEvaluate(StackEvaluate* stack);
int isEmptyEvaluate(StackEvaluate* stack);
void pushEvaluate(StackEvaluate* stack, double value);

#endif