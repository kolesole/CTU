#include "queue.h"

bool push(node_t** head, node_t** tail, int row, int col, int speed, int direction, int path_length) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "ERROR: cannot allocate memory for queue!\n");
        delete_queue(*head);
        return false;
    }

    new_node->row = row;
    new_node->col = col;
    new_node->speed = speed;
    new_node->direction = direction;
    new_node->path_length = path_length;
    new_node->next = NULL;

    if (*head == NULL) {
        *tail = new_node;
        *head = *tail;
    } else {
        (*tail)->next = new_node;
        *tail = new_node;
    }

    return true;
}

node_t* pop(node_t** head) {
    if (*head == NULL) {
        return NULL;
    }

    node_t* cur_node = *head;
    *head = (*head)->next;

    return cur_node;
}

void delete_queue(node_t* head) {
    while (head != NULL) {
        node_t* cur_node = head;
        head = head->next;
        free(cur_node);
    }
}