#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

static uint16_t num=0;

void * increment_and_print_even(void *ptr)
{
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    while (1) {
        pthread_mutex_lock(&mutex);
        if (num >= 30) {
            pthread_exit(NULL);
        }
        if (num%2!=0) {
            num++;
            printf("print_even: num=[%u]\n", num);
        }
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void * increment_and_print_odd(void *ptr)
{
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    while (1) {
        pthread_mutex_lock(&mutex);
        if (num >= 30) {
            pthread_exit(NULL);
        }
        if (num%2==0) {
            num++;
            printf("print_odd: num=[%u]\n", num);
        }
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main()
{
    pthread_t tid1, tid2;

    if (pthread_create(&tid1, NULL, increment_and_print_even, NULL))
    {
        perror("thread1 creation failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&tid2, NULL, increment_and_print_odd, NULL))
    {
        perror("thread2 creation failed");
        exit(EXIT_FAILURE);
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
