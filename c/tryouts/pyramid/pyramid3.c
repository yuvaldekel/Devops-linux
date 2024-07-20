#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

void init_string(char *string);
uint len_till_number(uint num);

typedef unsigned int uint; 

int main(int argc, char *argv[])
{
    int n = atoi(argv[argc -1 ]);
    uint len = len_till_number(n - 1);
    
    char *forward = malloc((len + 1) * sizeof(char));
    char *end_forward = forward;
    init_string(forward);

    char *reverse = malloc((len + 1) * sizeof(char));
    char *end_reverse = reverse;

    for (int i=n-1;i>=1;i--)
    {
        char curr_number[16];

        sprintf(curr_number, "%d", i);
        strcat(end_reverse, curr_number);
        end_reverse += strlen(curr_number);    
    }

    *end_reverse = '\0';

    printf("*");

    for (uint i=1;i<=n;i++)
    {
        printf("%s%d%s*", forward, i, end_reverse);

        char curr_number[16];
        sprintf(curr_number, "%d", i);

        uint curr_len = strlen(curr_number);
        end_reverse -= curr_len;

        if (i != n)
        {
            strcat(end_forward, curr_number);
            end_forward += curr_len;    
        }
    }

    end_reverse = reverse;

    for (uint i=n-1;i>=1;i--)
    {
        char curr_number[16];
        sprintf(curr_number, "%d", i);
        uint curr_len = strlen(curr_number);

        end_forward = end_forward - curr_len;
        *end_forward = '\0';  

        printf("%s%s*", forward, end_reverse);
        end_reverse = end_reverse + curr_len;
    }

    free(reverse);
    free(forward);

    printf("\n");
}

void init_string(char *string)
{
    uint len = strlen(string);

    for (uint i = 0; i < len; i++)
    {
        string[i] = '\0';
    }
}

uint len_till_number(uint num)
{
    uint total = 0;
    
    uint curr_w = 1;
    uint curr_biggest = 9;
    uint curr_lowest = 0;

    while (num >= curr_biggest)
    {
        total += (curr_biggest - curr_lowest) * curr_w;
        
        curr_lowest = curr_biggest;
        curr_biggest = curr_biggest * 10 + 9;

        curr_w++;
    }

    total += (num - curr_lowest) * curr_w;
    return total;    
}
