#include "post.h"

bool post_init(post_t** post, int indx) {
    *post = (post_t*)malloc(sizeof(post_t));
    if (*post == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for post!\n");
        return false;
    }

    (*post)->indx = indx;
    (*post)->max_even_path = 0;
    (*post)->max_odd_path = 0;
    (*post)->num_of_parents = 0;
    (*post)->num_of_children = 0;
    (*post)->size_of_children = 10;

    (*post)->children = (post_t**)malloc((*post)->size_of_children * sizeof(post_t*));
    if ((*post)->children == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for children!\n");
        free(*post);
        return false;
    }

    (*post)->val_of_routes = (int*)malloc((*post)->size_of_children * sizeof(int));
    if ((*post)->val_of_routes == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for val_of_routes!\n");
        free((*post)->children);
        free(*post);
        return false;
    }

    return true;
}

bool post_realloc(post_t** post) {
    (*post)->size_of_children *= 2;

    post_t** tmp_children = (post_t**)realloc((*post)->children, (*post)->size_of_children * sizeof(post_t*));
    if (tmp_children == NULL) {
        fprintf(stderr, "ERROR: Cannot reallocate memory for children!\n");
        return false;
    }
    (*post)->children = tmp_children;

    int* tmp_val_of_routes = (int*)realloc((*post)->val_of_routes, (*post)->size_of_children * sizeof(int));
    if (tmp_val_of_routes == NULL) {
        fprintf(stderr, "ERROR: Cannot reallocate memory for val_of_routes!\n");
        return false;
    }
    (*post)->val_of_routes = tmp_val_of_routes;

    return true;
}

void post_free(post_t* post) {
    free(post->children);
    free(post->val_of_routes);
    free(post);
}

void mark_posts_with_hut(post_t** sorted_post_array, int num_of_posts, int* num_of_huts) {
    int max_post = -1;
    for (int i = 0; i < num_of_posts; i++) {
        post_t* cur_post = sorted_post_array[i];
        if (cur_post->indx >= max_post) {
            cur_post->hut = true;
            (*num_of_huts)++;
        } else {
            cur_post->hut = false;
        }

        int cur_max_post = -1;
        for (int j = 0; j < cur_post->num_of_children; j++) {
            post_t* cur_child = cur_post->children[j];
            cur_max_post = cur_child->indx > cur_max_post ? cur_child->indx : cur_max_post;
        }

        if (max_post < cur_max_post) {
            max_post = cur_max_post;
        }
    }
}
