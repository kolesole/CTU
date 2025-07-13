#ifndef WORKERS_LIST_H
#define WORKERS_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

//structure to represent worker
typedef struct worker_t {
    pthread_t thread;         //the thread associated with this worker
    char* name;               //the name of the worker
    int place;                //worker specialization
    bool end;                 //flag for worker if he must go home
    struct worker_t* next;    //pointer to the next worker in the linked list
    struct worker_t* prev;    //pointer to the previous worker in the linked list
} worker_t;

extern pthread_mutex_t stdout_mutex;
extern pthread_mutex_t workers_list_mutex;

extern worker_t* workers_head;
extern worker_t* workers_tail;

//function to add worker to the workers list
bool add_worker(char* name, int place);
//function to find worker by name
worker_t* find_worker(char* name);
//function to delete worker from the workers list
void delete_worker(worker_t* worker);
//function to free memory
void free_list();

#endif //WORKERS_LIST_H
