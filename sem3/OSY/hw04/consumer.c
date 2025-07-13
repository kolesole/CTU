#include "consumer.h"

void* consumer_function(void* arg) {
    //getting thread number
    int thread_num = *(int*)arg;

    while (1) {
        //waiting for data to be received by the producer
        sem_wait(&semaphore);
        //closing the critical part of the code
        pthread_mutex_lock(&consumer_mutex);
        //flow termination condition(a thread has access to the data, but it is empty)
        if (head == NULL) {
            pthread_mutex_unlock(&consumer_mutex);
            break;
        }
        //getting first node
        node_t* node = remove_node();
        //node checking and performing action
        if (node != NULL) {
            printf("Thread %d:", thread_num);
            for (int i = 0; i < node->num; i++) {
                printf(" %s", node->text);
            }
            printf("\n");

            free(node->text);
            free(node);
        }
        //opening the mutex for access by other threads
        pthread_mutex_unlock(&consumer_mutex);
    }

    return NULL;
}