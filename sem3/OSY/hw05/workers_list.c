#include "workers_list.h"

bool add_worker(char* name, int place) {
    pthread_mutex_lock(&workers_list_mutex);

    //memory allocation for new worker
    worker_t* new_worker = (worker_t*)malloc(sizeof(worker_t));
    if (new_worker == NULL) {
        pthread_mutex_unlock(&workers_list_mutex);
        fprintf(stderr, "Error: Cannot allocate memory for worker!\n");
        return false;
    }

    //copying worker name
    new_worker->name = strdup(name);
    if (new_worker->name == NULL) {
        fprintf(stderr, "Error: Cannot allocate memory for worker name!\n");
        pthread_mutex_unlock(&workers_list_mutex);
        free(new_worker);
        return false;
    }

    new_worker->end = false;
    new_worker->place = place;
    new_worker->next = NULL;

    //adding a worker to the end of the workers list
    if (workers_head == NULL) {
        workers_head = new_worker;
        workers_tail = new_worker;
    } else {
        workers_tail->next = new_worker;
        new_worker->prev = workers_tail;
        workers_tail = new_worker;
    }

    pthread_mutex_unlock(&workers_list_mutex);

    return true;
}

worker_t* find_worker(char* name) {
    //start at the head of the workers list
    worker_t* worker = workers_head;
    while (worker != NULL) {
        //compare the given name with the current workers name
        if (strcmp(name, worker->name) == 0) {
            //if worker is found --> return pointer on worker
            return worker;
        }
        worker = worker->next;
    }
    //if no worker with the given name is found --> return NULL
    return NULL;
}

void delete_worker(worker_t* worker) {
    pthread_mutex_lock(&workers_list_mutex);

    //if the worker is NULL --> return
    if (!worker) {
        pthread_mutex_unlock(&workers_list_mutex);
        return;
    }

    //if the worker is the head of the workers list
    if (worker == workers_head) {
        if (workers_head != workers_tail) {      //if the workers list has more than one worker
            workers_head = workers_head->next;
            workers_head->prev = NULL;
        } else {                                 //if the workers list has only one worker
            workers_head = NULL;
            workers_tail = NULL;
        }
    }
    else if (worker == workers_tail) {           //if the worker is the tail of the workers list
        workers_tail = workers_tail->prev;
        workers_tail->next = NULL;
    } else {                                     //if the worker is between the head and the tail of workers list
        worker->next->prev = worker->prev;
        worker->prev->next = worker->next;
    }

    free(worker->name);
    free(worker);
    worker = NULL;

    pthread_mutex_unlock(&workers_list_mutex);
}

void free_list() {
    pthread_mutex_lock(&workers_list_mutex);

    while (workers_head) {                         //iterate through the list and free each worker
        worker_t* tmp = workers_head->next;
        free(workers_head->name);
        free(workers_head);
        workers_head = tmp;
    }

    workers_head = NULL;
    workers_tail = NULL;

    pthread_mutex_unlock(&workers_list_mutex);
}
