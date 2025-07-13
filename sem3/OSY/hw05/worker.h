#ifndef WORKER_H
#define WORKER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "work.h"
#include "utils.h"
#include "workers_list.h"

extern int num_of_places[7];
extern int num_of_workers[7];
extern int ready_places[7];
extern int available_works[7];
extern int parts[3][6];

extern pthread_mutex_t work_mutex;
extern pthread_cond_t work_cond;
extern pthread_mutex_t stdout_mutex;
extern pthread_mutex_t var_mutex;

extern bool eof;

//worker function
void* worker_function(void* arg);
//function to check if there is some available work
bool is_available_work(worker_t* worker);
//function to check if there is some available place for a worker
bool is_available_place(worker_t* worker);
//function to get and do work
void get_and_do_work(worker_t* worker);

#endif //WORKER_H
