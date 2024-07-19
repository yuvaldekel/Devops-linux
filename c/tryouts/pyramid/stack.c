#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"

node *create_node(char *string)
{
    node *nd = (node*) malloc(sizeof(node));
    
    if (nd == NULL)
    {
        return NULL;
    }

    nd->value = string;
    nd->next = NULL;
    return nd;
}

bool hasNext(node *nd)
{
    if (nd->next == NULL)
    {
        return false;
    }
    return true;
}

stack *create_stack(void)
{
    stack *stk = malloc(sizeof(stack));
    stk->first = NULL;
    return stk;
}

int push(stack *stk, char *value)
{
    node *nd = create_node(value);
    
    if (nd == NULL)
    {
        return 1;
    } 

    nd->next = stk->first;
}

char *pop(stack *stk)
{
    node *first_node = stk->first;

    if (! hasNext(first_node))
    {
        return NULL;
    }

    char *str = (char*) malloc(sizeof(char) * strlen(stk->first->value));
    str = first_node->value;

    stk->first = first_node->next;

    free(first_node);

    return str;
}