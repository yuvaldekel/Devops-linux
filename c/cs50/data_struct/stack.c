#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
    int size;
    int *stack;
}Stack;

Stack *create(void);
int push(Stack *stk, int num);
int  *pop(Stack *stk);
int print_stack(Stack *stk);

int main(void)
{
    Stack *stk = create();
    
    push(stk, 5);
    print_stack(stk);
    push(stk, 10);
    print_stack(stk);

    int *num = pop(stk);
    print_stack(stk);
    num = pop(stk);

    push(stk, 1);
    print_stack(stk);
    num = pop(stk);

}

Stack *create(void)
{
    Stack *stk = (Stack*) malloc(sizeof(int) + sizeof(int*));
    stk->size = 0;
    return stk;
}

int push(Stack *stk, int num)
{
    stk->size ++;
    int *tmp = (int*) realloc(stk->stack, sizeof(int) * stk->size);

    if (tmp == NULL)
    {
        free(stk->stack);
        return 1;
    }

    stk->stack = tmp;
    stk->stack[stk->size-1] = num;
}

int *pop(Stack *stk)
{
    if (stk->size == 0)
    {
        return NULL;
    }

    int *num = (int*) malloc(sizeof(int));
    *num = stk->stack[stk->size-1];

    stk->size --;
    int *tmp = (int*) realloc(stk->stack, sizeof(int) * stk->size);

    if (tmp == NULL & stk->size !=0)
    {
        free(stk->stack);
        return NULL;
    }

    stk->stack = tmp;
    return num;
}

int print_stack(Stack *stk)
{
    printf("[");
    for(int i=stk->size;i>0;i--)
    {
        printf("%d",stk->stack[i-1]);
        if (i != 1)
        {
            printf(",\n ");
        }
    }
    printf("]\n");
}