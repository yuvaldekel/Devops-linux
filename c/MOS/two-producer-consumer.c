#include <stdio.h>
#include <pthread.h>

#define MAX 100

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;
int buffer_array[2* MAX];

void *producer1(void *ptr);
void *producer2(void *ptr);
void *consumer(void *ptr);
void print_array(int size,int array[]);
void thread_sleep(void);

int main(int argc, char * argv[])
{
    pthread_t pro1, pro2, con;

    pthread_mutex_init(&the_mutex, 0);
    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);
    
    pthread_create(&con, 0, consumer, 0);
    pthread_create(&pro1, 0, producer1, 0);
    pthread_create(&pro2, 0, producer2, 0);
    
    pthread_join(pro1, 0);
    pthread_join(pro2, 0);
    pthread_join(con, 0);
    
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);

    print_array(2 * MAX, buffer_array);
}

void *producer1(void *ptr)
{
    int i;

    for (i=1;i<=MAX;i++)
    {
        pthread_mutex_lock(&the_mutex);
        while (buffer != 0) pthread_cond_wait(&condp, &the_mutex);
        buffer = i;
        printf("producer1 here, %d. ", buffer);
        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}

void *producer2(void *ptr)
{
    int i;

    for (i=1;i<=MAX;i++)
    {
        pthread_mutex_lock(&the_mutex);
        while (buffer != 0) pthread_cond_wait(&condp, &the_mutex);
        buffer = i;
        printf("producer2 here, %d. ", buffer);
        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}

void *consumer(void *ptr)
{
    int i;

    for (i=1;i<=2 * MAX;i++)
    {
        pthread_mutex_lock(&the_mutex);
        while (buffer == 0) pthread_cond_wait(&condc, &the_mutex);
        printf("consumer here, %d\n", buffer);
        buffer_array[i -1] = buffer;
        buffer = 0;
        pthread_mutex_unlock(&the_mutex);
        pthread_cond_broadcast(&condp);
    }
    pthread_exit(0);
}

void print_array(int size,int array[])
{
    int i;
    printf("[");
    for (i=0;i<size;i++)
    {
        printf("%d (%d)", array[i] ,i);
        if (i != size -1)
            printf(",");
        
    }
    printf("]\n");
}