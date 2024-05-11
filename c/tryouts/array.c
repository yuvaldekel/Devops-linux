#include <stdio.h>
#include <stdlib.h>

int arr(char a[]);

int main(int argc, char* argv[]){

    char *heapArray = (char*) malloc(3 * sizeof(char));
    *heapArray = '0';
   *(heapArray + 1) = '1';
   *(heapArray + 2) = '\0';

    printf("%s\n", (heapArray));

    char nums[4] = {'1', '2', '3', '4'};
    printf("%li\n", sizeof(nums));

    printf("%p\n", &nums);
    arr(nums);
}

int arr(char a[])
{
    printf("%s\n", a+1);
    printf("%p\n", &a);
}