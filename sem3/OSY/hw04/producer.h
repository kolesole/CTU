#ifndef PRODUCER_H
#define PRODUCER_H

#include <stdio.h>
#include <semaphore.h>

#include "linked_list.h"

extern sem_t semaphore;
extern int num_of_cons;
//producer function
void* producer_function(void* arg);

#endif //PRODUCER_H
