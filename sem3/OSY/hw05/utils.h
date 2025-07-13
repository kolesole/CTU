#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdbool.h>
#include <pthread.h>

#include "work.h"

extern int num_of_workers[7];

extern pthread_mutex_t var_mutex;
extern pthread_mutex_t workers_list_mutex;

extern bool eof;

//function to find string in array
int find_string_in_array(const char** array, int length, char* what);
//function to check(with mutex) if EOF is received
bool check_eof();
//function to check(with mutex) if worker must go home
bool check_end(worker_t* worker);
//function to check(with mutex) num of workers
int check_num_of_workers();

#endif //UTILS_H
