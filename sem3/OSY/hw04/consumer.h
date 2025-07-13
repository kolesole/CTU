#ifndef CONSUMER_H
#define CONSUMER_H

#include <semaphore.h>

#include "linked_list.h"

extern sem_t semaphore;
extern pthread_mutex_t consumer_mutex;
//consumer function
void* consumer_function(void* arg);

#endif //CONSUMER_H
