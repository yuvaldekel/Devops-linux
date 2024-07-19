#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include "linked_list.h"

void add_node(double value, node  * last_node, node *first_node);


int main(int argc, char *argv[])
{
    int n = 5000000;
    int inside = 0;

    node * x_first_point = NULL;
    node * x_last_point = NULL;

    node * y_first_point = NULL;
    node * y_last_point = NULL;


    for(int i=0;i<n;i++)
    {
        double x = ((float) rand() * 2 / RAND_MAX) - 1;
        double y = ((float) rand() * 2 / RAND_MAX) - 1; 
        
        add_node(x, x_last_point, x_first_point);
        add_node(y, y_last_point, y_first_point);

        double sqr_x = pow(x, 2);
        double sqr_y = pow(y, 2);
        double distance = sqrt(sqr_x + sqr_y);

        if (distance <= 1)
        {
            inside++;
        }
    }

    double pi = 4 * ((double) inside / n);
    printf("%f\n", pi);
}


void add_node(double value, node *last_node, node *first_node)
{
    node *current = create(value);

    if (current == NULL)
    {
        return 1;
    }

    if (last_node != NULL)
    {
        set_next(last_node, current);
    }

    if (first_node == NULL)
    {
        first_node = current;
    }

    last_node = current;
}