#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//structure to represent node in queue
typedef struct node_t {
    int indx;
    struct node_t* next;
} node_t;

//function to push new node in queue
bool push(node_t** head, node_t** tail, int indx);
//function to pop firs node from queue
node_t* pop(node_t** head);
//function to free memory for queue
void delete_queue(node_t* head);

#endif //QUEUE_H
