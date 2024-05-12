#include <stdio.h>
#include <stdlib.h>


typedef struct two_int
{
   int num1;
   int num2;
}two_int;


int* swap_numbers(int num1, int num2);

int main(void)
{
    int num1 = 5;
    int num2 = 7;
    printf("num1 = %d, num2 = %d\n", num1, num2);

    //two_int  number =  {num1, num2};
    //two_int nums = swap_numbers(number);
    //num1 = nums.num1;
    //num2 = nums.num2;

    int *nums = swap_numbers(num1, num2);
    num1 = nums[0];
    num2 = nums[1];
    printf("num1 = %d, num2 = %d\n", num1, num2);

}

//two_int swap_numbers(two_int nums)
//{
  //  nums.num1 = nums.num1 ^ nums.num2;
  //  nums.num2 = nums.num1 ^ nums.num2;
  //  nums.num1 = nums.num1 ^ nums.num2;
  //  return nums;
//}

int* swap_numbers(int num1, int num2)
{
    int *nums = (int*) malloc(2 * sizeof(int));
    num1 = num1 ^ num2;
    num2 = num1 ^ num2;
    num1 = num1 ^ num2;
    nums[0] = num1;
    nums[1] = num2;
    return nums;
}