#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

void print_pyramid(int num);
int string_to_int(char* string);

typedef unsigned int uint; 

int main(int argc, char *argv[])
{

    char *arg_num = argv[argc -1];
    uint n = string_to_int(arg_num);

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

int string_to_int(char* string)
{
    int number = 0;
    
    int length = strlen(string);
    int i = 0;

    for(i=0;i<length;i++){
        int digit = string[i] - '0';
        number = number * 10 + digit;
    }
 
    return number;
}