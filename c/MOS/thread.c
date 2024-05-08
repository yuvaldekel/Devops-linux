#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>

#define NUMBER_OF_THREADS 10 

void *print_hello_world(void *tid);

int main(int argc, char *argv[])
{
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i;

    for(i=0;i<NUMBER_OF_THREADS;i++)
    {
        printf("Main here. Creating thread %d\n", i);
        int* thread_i =  (int*) malloc(sizeof(int));
        *thread_i = i;
        
        status = pthread_create(&threads[i], NULL, print_hello_world, (void *) thread_i);
        if (status != 0){
            printf("Oops. pthread_create returned error code %d\n", status);
            exit(-1);
        }
    }
    sleep(1);
}

void *print_hello_world(void *tid)
{
    int n = *(int*)tid;
    printf("Hello World. Greetings from thread %d\n", n);
    free(tid);
    pthread_exit(NULL);
}