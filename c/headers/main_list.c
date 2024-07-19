#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"


int main(void)
{
    node *current_node = NULL;
    node *last_node = NULL;
    node *first_node = NULL;

    for(int i=0;i<3;i++)
    {
        int value;

        printf("Type a number: ");
        scanf("%d", &value);

        current_node = create(value);
        
        if (current_node == NULL)
        {
            return 1;
        }

        if (last_node != NULL)
        {
            set_next(last_node, current_node);
        }

        if (first_node == NULL)
        {
            first_node = current_node;
        }

        last_node = current_node;
    }
    
    printf("%d\n", first_node->value);

    while(has_next(first_node))
    {
        node *next = get_next(first_node);
        
        if (next != first_node)
        {
            free(first_node);
        }

        first_node = next;
        printf("%d\n", first_node->value);
    }

    free(first_node);
    
    return 0;
}