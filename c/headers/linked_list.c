#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"


node *create(int num)
{
    node *nd = (node*) malloc(sizeof(node));
    
    if (nd == NULL)
    {
        return NULL;
    }

    nd->value = num;
    nd->next = NULL;
    return nd;
}

void set_next(node *nd1, node *nd2)
{
    nd1->next = nd2;
}

node *get_next(node *nd)
{
    if (nd == NULL)
    {
        return NULL;
    }
    
    node *next_nd = nd->next;
    return next_nd;
}

bool has_next(node *nd)
{
    if (nd->next !=NULL)
    {
        return true;
    }

    return false;
}