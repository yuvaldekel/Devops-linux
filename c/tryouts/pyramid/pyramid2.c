#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

void print_pyramid(int num);

typedef unsigned int uint; 

int main(int argc, char *argv[])
{
    uint n = atoi(argv[argc -1 ]);

    printf("*");

    uint i;
    //stack *stk = create_stack();

    for (i=1;i<=n;i++)
    {
        print_pyramid(i);
        printf("*");

        //if (i != n)
        //{
        //   push(stk, "4"); 
        //}
    }

    for (i=n-1;i>=1;i--)
    {
        print_pyramid(i);
        printf("*");
    }

    printf("\n");
}


void print_pyramid(int num)
{
    uint i;

    for (i=1;i<num;i++)
    {
        printf("%d", i);
    }

    for (i=num;i>=1;i--)
    {
        printf("%d", i);
    }
}