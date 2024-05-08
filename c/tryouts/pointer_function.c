#include <stdio.h>
#include <pthread.h>

#define MAX 1000

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp; 
int buffer = 0;

void *producer(void *ptr);
void *consumer(void *ptr);

int main(int argc, char * argv[])
{
    int num = 5;
    int *point = &num;
    printf("main here     %d\n", *point);    
    producer((void*) point);
    consumer((void*) point);

    return 0;
}

void *producer(void *ptr)
{
    int * point;
    point = (int*) ptr;
    printf("producer here %d\n", *point);    
}

void *consumer(void *ptr)
{
    int * point;
    point = (int*) ptr;
    printf("consumer here %d\n", *point);    
}