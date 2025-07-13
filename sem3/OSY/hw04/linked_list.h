#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
//linked list element structure
typedef struct node_t {
    struct node_t* next;
    int num;
    char* text;
} node_t;

extern node_t* head;
extern node_t* tail;
extern sem_t semaphore;
extern pthread_mutex_t list_mutex;
//function to add a node to the linked list
bool add_node(int num, char* text);
//function to remove a node from the linked list
node_t* remove_node();
//function to free up memory
void free_list();

#endif //LINKED_LIST_H
