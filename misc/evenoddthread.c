#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX 100

volatile int count = 0;

pthread_mutex_t mutex;
pthread_cond_t cond;

void *printeven()
{
    while (count < MAX)
    {
        pthread_mutex_lock(&mutex);

        while (count % 2 != 0)
            pthread_cond_wait(&cond, &mutex);

        printf("%d ", count++);

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
    pthread_exit(0);
}

void *printodd()
{
    while (count < MAX)
    {
        pthread_mutex_lock(&mutex);

        while (count % 2 != 1)
            pthread_cond_wait(&cond, &mutex);

        printf("%d ", count++);

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
    pthread_exit(0);
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_mutex_init(&mutex, 0);
    pthread_cond_init(&cond, 0);

    pthread_create(&thread1, 0, &printeven, NULL);
    pthread_create(&thread2, 0, &printodd, NULL);

    pthread_join(thread1, 0);
    pthread_join(thread2, 0);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    printf("\n");
    return 0;
}