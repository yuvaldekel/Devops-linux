#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node{
    int value;
    struct Node *next;
}node;

node *create(int num);
void set_next(node *nd1, node *nd2);
node *get_next(node *nd1);
bool has_next(node * nd);

int main(void)
{
    node *nd1 = create(5);
    if (nd1 == NULL)
    {
        return 1;
    }

    node *nd2 = create(51);
    if (nd2 == NULL)
    {
        return 1;
    }

    node *nd3 = create(11);
    if (nd2 == NULL)
    {
        return 1;
    }
    
    set_next(nd1, nd2);
    node *nd_next = get_next(nd1);
    set_next(nd_next, nd3);
    
    printf("%d\n", nd1->value);
    while(has_next(nd1))
    {
        node *next = get_next(nd1);
        if (next != nd1)
        {
            free(nd1);
        }
        nd1 = next;
        printf("%d\n", nd1->value);
    }

    return 0;
}

node *create(int num)
{
    node *nd = (node*) malloc(sizeof(int) + sizeof(struct Node*));
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