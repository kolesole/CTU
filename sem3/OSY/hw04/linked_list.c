#include "linked_list.h"

bool add_node(int num, char* text) {
    //closing the list mutex
    pthread_mutex_lock(&list_mutex);
    //creating a new node
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        pthread_mutex_unlock(&list_mutex);
        fprintf(stderr, "Error: Cannot allocate memory for node!\n");
        return false;
    }

    new_node->num = num;
    new_node->text = text;
    new_node->next = NULL;
    //adding a new node to the end of the linked list
    if (head == NULL) {
        head = new_node;
        tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
    //opening the list mutex
    pthread_mutex_unlock(&list_mutex);
    //increase the semaphore so that consumers can see that new data are allowed
    sem_post(&semaphore);
    return true;
}

node_t* remove_node() {
    //closing the list mutex
    pthread_mutex_lock(&list_mutex);
    //check if there is anything in the linked list
    if (head == NULL) {
        pthread_mutex_unlock(&list_mutex);
        return NULL;
    }
    //remove first node
    node_t* tmp = head;
    head = head->next;
    //opening the list mutex
    pthread_mutex_unlock(&list_mutex);
    return tmp;
}

void free_list() {
    //closing the list mutex
    pthread_mutex_lock(&list_mutex);
    //remove all nodes
    while (head != NULL) {
        node_t* tmp = head->next;
        free(head->text);
        free(head);
        head = tmp;
    }
    head = NULL;
    tail = NULL;
    //opening the list mutex
    pthread_mutex_unlock(&list_mutex);
}
