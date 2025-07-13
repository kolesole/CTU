#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
//structure for queue node
typedef struct node_t {
    struct node_t* next;
    int row, col;
    int speed;
    int direction;
    int path_length;
} node_t;
//function to push in queue
bool push(node_t** head, node_t** tail, int row, int col, int speed, int direction, int path_length);
//function to pop from queue
node_t* pop(node_t** head);
//function to free memory for queue
void delete_queue(node_t* head);

#endif //QUEUE_H
