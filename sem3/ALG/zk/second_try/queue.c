#include "queue.h"

bool push(node_t** head, node_t** tail, int mouse_pos, int cat_pos, int path_len, int num_of_noisy_nodes, int num_of_cat_jmps, int prev) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "ERROR: cannot allocate memory for queue!\n");
        delete_queue(*head);
        return false;
    }

    new_node->mouse_pos = mouse_pos;
    new_node->prev = prev;
    new_node->cat_pos = cat_pos;
    new_node->path_len = path_len;
    new_node->num_of_noisy_nodes = num_of_noisy_nodes;
    new_node->num_of_cat_jmps = num_of_cat_jmps;
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

