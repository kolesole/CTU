#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "linked_list.h"
#include "producer.h"
#include "consumer.h"

node_t* head = NULL;              //global head for linked list
node_t* tail = NULL;              //global tail for linked list
sem_t semaphore;                  //global semaphore to control how much data is transferred
pthread_mutex_t list_mutex;       //global mutex to ensure that only one thread has access to linked list
pthread_mutex_t consumer_mutex;   //global mutex to ensure that only one consumer has access to data
int num_of_cons;                  //global number of consumers

int main(int argc, char *argv[]) {
    //getting how many consumers must be
    num_of_cons = argc == 2 ? atoi(argv[1]) : 1;
    if (num_of_cons < 1 || num_of_cons > sysconf(_SC_NPROCESSORS_ONLN)) {
        fprintf(stderr, "Error: Wrong number of consumers!\n");
        return 1;
    }
    //consumers mutex initialization
    if (pthread_mutex_init(&consumer_mutex, NULL) != 0) {
        fprintf(stderr, "Error: Failed to initialize mutex!\n");
        return 2;
    }
    //liked list mutex initialization
    if (pthread_mutex_init(&list_mutex, NULL) != 0) {
        pthread_mutex_destroy(&consumer_mutex);
        fprintf(stderr, "Error: Failed to initialize mutex!\n");
        return 2;
    }
    //semaphore initialization to control the amount of data
    if (sem_init(&semaphore, 0, 0) != 0) {
        pthread_mutex_destroy(&consumer_mutex);
        pthread_mutex_destroy(&list_mutex);
        fprintf(stderr, "Error: Failed to initialize semaphore!\n");
        return 2;
    }
    //producer initialization
    pthread_t producer;
    if (pthread_create(&producer, NULL, producer_function, NULL) != 0) {
        pthread_mutex_destroy(&consumer_mutex);
        pthread_mutex_destroy(&list_mutex);
        sem_destroy(&semaphore);
        fprintf(stderr, "Error: Failed to create producer thread!\n");
        return 2;
    }
    //consumers initialization
    pthread_t consumers[num_of_cons];
    int consumers_indxs[num_of_cons];
    for (int i = 0; i < num_of_cons; i++) {
         consumers_indxs[i] = i + 1;

        if (pthread_create(&consumers[i], NULL, consumer_function, &consumers_indxs[i]) != 0) {
            free_list();
            pthread_mutex_destroy(&consumer_mutex);
            pthread_mutex_destroy(&list_mutex);
            sem_destroy(&semaphore);
            fprintf(stderr, "Error: Failed to create consumer thread %d!\n", i);
            return 2;
        }
    }
    //waiting for all consumers
    for (int i = 0; i < num_of_cons; i++) {
        if (pthread_join(consumers[i], NULL) != 0) {
            pthread_mutex_destroy(&consumer_mutex);
            free_list();
            sem_destroy(&semaphore);
            fprintf(stderr, "Error: Failed to join consumer thread %d!\n", i);
            return 2;
        }
    }
    //waiting for producer
    int ret;
    if (pthread_join(producer, (void**)&ret) != 0) {
        free_list();
        pthread_mutex_destroy(&consumer_mutex);
        pthread_mutex_destroy(&list_mutex);
        sem_destroy(&semaphore);
        fprintf(stderr, "Error: Failed to join producer thread!\n");
        return 2;
    }
    //freeing memory
    free_list();
    //consumers mutex destruction
    if (pthread_mutex_destroy(&consumer_mutex) != 0) {
        pthread_mutex_destroy(&list_mutex);
        sem_destroy(&semaphore);
        fprintf(stderr, "Error: Failed to destroy consumers mutex!\n");
        return 2;
    }
    //list mutex destruction
    if (pthread_mutex_destroy(&list_mutex) != 0) {
        sem_destroy(&semaphore);
        fprintf(stderr, "Error: Failed to destroy list mutex!\n");
        return 2;
    }
    //data semaphore destruction
    if (sem_destroy(&semaphore) != 0) {
        fprintf(stderr, "Error: Failed to destroy semaphore!\n");
        return 2;
    }

    return ret;
}
