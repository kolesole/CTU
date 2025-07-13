#include "utils.h"

bool post_array_init(post_t*** post_array, int num_of_posts) {
    *post_array = (post_t**)malloc(sizeof(post_t*) * num_of_posts);
    if (*post_array == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for post_array!\n");
        return false;
    }

    for (int i = 0; i < num_of_posts; i++) {
        if (!post_init(&(*post_array)[i], i)) {
            post_array_free(*post_array, i);
            return false;
        }
    }

    return true;
}

void post_array_free(post_t** post_array, int num_of_posts) {
    for (int i = 0; i < num_of_posts; i++) {
        post_free(post_array[i]);
    }

    free(post_array);
}

bool read_input(post_t*** post_array, int* num_of_posts, int* num_of_routes) {
    if (scanf("%d %d", num_of_posts, num_of_routes) != 2) {
        fprintf(stderr, "ERROR: Cannot read input!\n");
        return false;
    }

    if (!post_array_init(post_array, *num_of_posts)) {
        return false;
    }

    for (int i = 0; i < *num_of_routes; i++) {
        int post1_indx, post2_indx, route_val;

        if (scanf("%d %d %d", &post1_indx, &post2_indx, &route_val) != 3) {
            fprintf(stderr, "ERROR: Cannot read input!\n");
            post_array_free(*post_array, *num_of_posts);
            return false;
        }

        if ((*post_array)[post1_indx - 1]->size_of_children <= (*post_array)[post1_indx - 1]->num_of_children) {
            if (!post_realloc(&(*post_array)[post1_indx - 1])) {
                post_array_free(*post_array, *num_of_posts);
                return false;
            }
        }

        (*post_array)[post2_indx - 1]->num_of_parents++;
        (*post_array)[post1_indx - 1]->children[(*post_array)[post1_indx - 1]->num_of_children] = (*post_array)[post2_indx - 1];
        (*post_array)[post1_indx - 1]->val_of_routes[(*post_array)[post1_indx - 1]->num_of_children] = route_val;
        (*post_array)[post1_indx - 1]->num_of_children++;
    }

    return true;
}
