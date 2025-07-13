#ifndef WORK_H
#define WORK_H

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#include "workers_list.h"

extern int num_of_places[7];
extern int ready_places[7];
extern int available_works[7];
extern int num_of_workers[7];
extern int parts[3][6];
extern int num_of_est_works[3][6];
extern const int processes[3][6];

extern pthread_mutex_t stdout_mutex;
extern pthread_cond_t work_cond;
extern pthread_mutex_t var_mutex;

//function toget and do work for a worker with a specialization nuzky
void get_and_do_work_nuzky(char* name);
//function to get and do work for a worker with a specialization vrtacka
void get_and_do_work_vrtacka(char* name);
//function to get and do work for a worker with a specialization ohybacka
void get_and_do_work_ohybacka(char* name);
//function to get and do work for a worker with a specialization svarecka
void get_and_do_work_svarecka(char* name);
//function to get and do work for a worker with a specialization lakovna
void get_and_do_work_lakovna(char* name);
//function to get and do work for a worker with a specialization sroubovak
void get_and_do_work_sroubovak(char* name);
//function to get and do work for a worker with a specialization freza
void get_and_do_work_freza(char* name);
//function to check if any new work may appear for a worker
bool should_worker_wait(int place);

#endif //WORK_H
