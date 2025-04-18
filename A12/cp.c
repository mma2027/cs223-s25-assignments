// Author : Maxfield Ma
// Date : 4/18/2025
// Description : Implementing producer and consumer solution
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

#define N 10

struct thread{
    pthread_t id;
    int* ptr;
};

int produce_item() {
    return rand() % 10;
}

void consume_item(int item) {
    printf("Received item: %d\n", item);
}

void* consumer(void* input){
    struct thread* i = (struct thread*) input;
    int *queue = i->ptr;
    int index = 0;

    while(1){
        if (queue[index] != -1){
            consume_item(queue[index]);
            //set space as "empty" and update index
            queue[index] = -1;
            index = (index + 1) % N;
        }
        sleep(1);
    }
    return NULL;
}

void* producer(void* input){
    struct thread* i = (struct thread*) input;
    int *queue = i->ptr;
    int index = 0;

    while(1){
        //if the next space is available, produce item and update index
        if (queue[(index + 1) % N] == -1){
            queue[index] = produce_item();
            index = (index + 1) % N;
        }
        sleep(1);
    }
    return NULL;
}


int main() {
    // todo
    struct thread threads[2];
    int queue[N];

    for (int i = 0; i < N; i++)
        queue[i] = -1;

    threads[0].ptr = queue;
    threads[1].ptr = queue;

    pthread_create(&threads[0].id, NULL, producer, &threads[0]);
    pthread_create(&threads[0].id, NULL, consumer, &threads[1]);

    pthread_join(threads[0].id, NULL);
    pthread_join(threads[1].id, NULL);
    return 0;
}

