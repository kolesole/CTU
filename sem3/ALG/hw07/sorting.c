#include "sorting.h"

bool topological_sort(post_t** post_array, post_t*** sorted_post_array, int num_of_posts) {
    node_t* head = NULL;
    node_t* tail = NULL;

    if (!push(&head, &tail, 0)) return false;

    int i = 0;
    while (head != NULL) {
        node_t* node = pop(&head);
        if (node == NULL) {
            return false;
        }

        post_t* post = post_array[node->indx];
        free(node);

        (*sorted_post_array)[i] = post;
        post->indx = i++;

        for (int j = 0; j < post->num_of_children; j++) {
            post_t* post_child = post->children[j];
            post_child->num_of_parents--;

            if (post_child->num_of_parents == 0) {
                if (!push(&head, &tail, post_child->indx)) {
                    return false;
                }
            }
        }
    }

    return true;
}
