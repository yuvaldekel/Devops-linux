#include <stdio.h>
#include <stdbool.h>

int size = 5;

int main(void)
{
    int array[] = {2,7,5,1,8};

    int i;
    bool check = true;
    while(check)
    {
        check =false;
        for(i=0;i<size-1;i++)
        {
            if(array[i]>array[i+1])
            {
                check = true;
                array[i] = array[i] ^ array[i+1];
                array[i+1] = array[i] ^ array[i+1];
                array[i] = array[i] ^ array[i+1];
            }
        }

    }

    for(i=0;i<size;i++)
    {
        printf("%d\n",array[i]);
    }
    
}