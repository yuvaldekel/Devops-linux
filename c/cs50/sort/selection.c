#include <stdio.h>

int const size = 5;

int main(void)
{
    int array[] = {2,7,5,1,8};

    int min, i,j;
    for(i=0;i<size-1;i++)
    {
        min = i;
        for(j=i+1;j<size;j++)
        {
            if(array[j]<=array[min])
            {
                min = j;
            }
        }
        if (min != i){
            array[min] = array[i] ^ array[min];
            array[i] = array[i] ^ array[min];
            array[min] = array[i] ^ array[min];
        }
    }

    for(i=0;i<size;i++)
    {
        printf("%d\n",array[i]);
    }
    
}