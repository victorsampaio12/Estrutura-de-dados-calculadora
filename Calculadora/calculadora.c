#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calculadora.h"

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 512

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    double data[MAX_STACK_SIZE];
    int top;
} Stack;

typedef struct {
    char* data[MAX_STACK_SIZE];
    int top;
} StringStack;

void push(Stack* stack, double value) {
    if (stack->top < MAX_STACK_SIZE) {
        stack->data[stack->top++] = value;
    } else {
        printf("Stack overflow\n");
    }
}

double pop(Stack* stack) {
    if (stack->top > 0) {
        return stack->data[--stack->top];
    } else {
        printf("Stack underflow\n");
        return 0;
    }
}

void pushString(StringStack* stack, char* value) {
    if (stack->top < MAX_STACK_SIZE) {
        stack->data[stack->top++] = strdup(value);
    } else {
        printf("String stack overflow\n");
    }
}

char* popString(StringStack* stack) {
    if (stack->top > 0) {
        return stack->data[--stack->top];
    } else {
        printf("String stack underflow\n");
        return "";
    }
}

int is_operator(char* token) {
    return (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
            strcmp(token, "*") == 0 || strcmp(token, "/") == 0 ||
            strcmp(token, "^") == 0);
}

int is_function(char* token) {
    return (strcmp(token, "raiz") == 0 || strcmp(token, "sen") == 0 ||
            strcmp(token, "cos") == 0 || strcmp(token, "tg") == 0 ||
            strcmp(token, "log") == 0);
}

float getValor(char* str) {
    Stack stack = { .top = 0 };
    char expr[MAX_EXPR_SIZE];
    strcpy(expr, str);
    
    char* token = strtok(expr, " ");
    while (token != NULL) {
        if (is_operator(token)) {
            double b = pop(&stack);
            double a = pop(&stack);
            if (strcmp(token, "+") == 0) push(&stack, a + b);
            else if (strcmp(token, "-") == 0) push(&stack, a - b);
            else if (strcmp(token, "*") == 0) push(&stack, a * b);
            else if (strcmp(token, "/") == 0) push(&stack, a / b);
            else if (strcmp(token, "^") == 0) push(&stack, pow(a, b));
        } else if (is_function(token)) {
            double a = pop(&stack);
            if (strcmp(token, "raiz") == 0) push(&stack, sqrt(a));
            else if (strcmp(token, "sen") == 0) push(&stack, sin(a * M_PI / 180.0));
            else if (strcmp(token, "cos") == 0) push(&stack, cos(a * M_PI / 180.0));
            else if (strcmp(token, "tg") == 0) push(&stack, tan(a * M_PI / 180.0));
            else if (strcmp(token, "log") == 0) push(&stack, log10(a));
        } else {
            push(&stack, atof(token));
        }
        token = strtok(NULL, " ");
    }
    return (float)pop(&stack);
}

char* getFormaInFixa(char* str) {
    StringStack stack = { .top = 0 };
    char expr[MAX_EXPR_SIZE];
    static char output[MAX_EXPR_SIZE];

    strcpy(expr, str);
    char* token = strtok(expr, " ");
    while (token != NULL) {
        if (is_operator(token) || is_function(token)) {
            char* op2 = popString(&stack);
            char* op1 = "";
            if (!is_function(token)) {
                op1 = popString(&stack);
            }
            char new_expr[MAX_EXPR_SIZE];
            if (is_function(token)) {
                sprintf(new_expr, "%s(%s)", token, op2);
            } else {
                sprintf(new_expr, "(%s %s %s)", op1, token, op2);
            }
            pushString(&stack, new_expr);
        } else {
            pushString(&stack, token);
        }
        token = strtok(NULL, " ");
    }
    strcpy(output, popString(&stack));
    return output;
}
