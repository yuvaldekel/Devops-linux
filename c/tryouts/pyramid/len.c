#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

int main(int argc, char *argv[])
{
    uint num = atoi(argv[argc -1 ]);
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
    
    printf("%d\n", total);
}