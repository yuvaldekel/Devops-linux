#include <stdio.h>
#include <stdlib.h>

int arr(char a[]);

int main(int argc, char* argv[])
{

    char* heapArray =  (char*) calloc(5 ,sizeof(char));
    heapArray = "123456";
    printf("%s\n", heapArray);

    char nums[4] = {'1', '2', '3', '4'};
    printf("%li\n", sizeof(nums));

    printf("%p\n", &nums);
    arr(nums);
}

int arr(char a[])
{
    printf("%s\n", a);
    printf("%p\n", &a);
}