#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    char *value;
    struct Node *next;
}node;

typedef struct Stack{
    node *first;
}stack;

node *create_node(char *string);
bool hasNext(node *nd);
stack *create_stack(void);
int push(stack *stk, char *value);
char *pop(stack *stk);