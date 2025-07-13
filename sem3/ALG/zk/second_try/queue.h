#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//structure to represent node in queue
typedef struct node_t {
    int mouse_pos;
    int cat_pos;
    int prev;
    int path_len;
    int num_of_noisy_nodes;
    int num_of_cat_jmps;
    struct node_t* next;
} node_t;

//function to push new node in queue
bool push(node_t** head, node_t** tail, int mouse_pos, int cat_pos, int path_len, int num_of_noisy_nodes, int num_of_cat_jmps, int prev);
//function to pop firs node from queue
node_t* pop(node_t** head);
//function to free memory for queue
void delete_queue(node_t* head);

#endif //QUEUE_H
