#include <stdio.h>

typedef unsigned int uint;

int main(void)
{
    uint num = 10000;
    uint total = 0;
    uint curr_w = 1;
    uint curr_len = 9;
    uint curr_biggest = 9;
    uint passed = 0;

    while (num >= curr_biggest)
    {
        total += curr_len * curr_w;
        
        passed += curr_len;
        curr_len *= 10;
        curr_biggest = curr_biggest * 10 + 9;
        curr_w++;
    }

    total += (num - passed) * curr_w;
    printf("%d\n", total);
}