#include <stdio.h>
#include <pthread.h>

#define MAX 1000

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp; 
int buffer = 0;
int buffer_array[MAX]; 

void *producer(void *ptr);
void *consumer(void *ptr);
void print_array(int size,int array[]);


int main(int argc, char * argv[])
{
    pthread_t pro, con;
    
    pthread_mutex_init(&the_mutex, 0);
    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);
    
    pthread_create(&con, 0, consumer, 0);
    pthread_create(&pro, 0, producer, 0);
    
    pthread_join(pro, 0);
    pthread_join(con, 0);
    
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);

    print_array(MAX, buffer_array);
}

void *producer(void *ptr)
{
    int i;

    for (i=1;i<=MAX;i++)
    {
        pthread_mutex_lock(&the_mutex);
        while (buffer != 0) pthread_cond_wait(&condp, &the_mutex);
        buffer = i;
        printf("producer here %d. ", buffer);
        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&the_mutex);        
    }
    pthread_exit(0);
}

void *consumer(void *ptr)
{
    int i;

    for (i=1;i<=MAX;i++)
    {
        pthread_mutex_lock(&the_mutex);
        while (buffer == 0) pthread_cond_wait(&condc, &the_mutex);
        printf("consumer here %d\n", buffer);
        buffer_array[i -1] = buffer;
        buffer = 0;
        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&the_mutex);        
    }
    pthread_exit(0);
}

void print_array(int size,int array[])
{
    int i;
    printf("[");
    for (i=0;i<size;i++)
    {
        printf("%d", array[i]);
        if (i != size -1) 
            printf(",");
    }
    printf("]\n");
}