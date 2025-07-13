#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "post.h"
#include "sorting.h"

//function to find max path to each post
void find_max_path(post_t** sorted_poat_array, int num_of_posts);

int main() {
    int num_of_posts, num_of_routes;
    post_t** post_array;
    if (!read_input(&post_array, &num_of_posts, &num_of_routes)) {
        return -1;
    }

    post_t** sorted_post_array = (post_t**)malloc(num_of_posts * sizeof(post_t*));
    if (sorted_post_array == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for sorted array!\n");
        post_array_free(post_array, num_of_posts);
        return -1;
    }

    if (!topological_sort(post_array, &sorted_post_array, num_of_posts)) {
        fprintf(stderr, "ERROR: Cannot topological sort!\n");
        free(sorted_post_array);
        post_array_free(post_array, num_of_posts);
        return -1;
    }
    free(post_array);

    int num_of_huts = 0;
    mark_posts_with_hut(sorted_post_array, num_of_posts, &num_of_huts);

    find_max_path(sorted_post_array, num_of_posts);

    printf("%d %d\n", sorted_post_array[num_of_posts - 1]->max_even_path, num_of_huts);

    post_array_free(sorted_post_array, num_of_posts);

    return 0;
}

void find_max_path(post_t** sorted_poat_array, int num_of_posts) {
    for (int i = 0; i < num_of_posts; i++) {
        post_t* post = sorted_poat_array[i];
        for (int j = 0; j < post->num_of_children; j++) {
            post_t* child = post->children[j];

            if (post->indx == 0) {
                child->max_odd_path = post->max_even_path + post->val_of_routes[j];
                continue;
            }

            if (post->max_even_path != 0) {
                int tmp = post->max_even_path + post->val_of_routes[j];
                child->max_odd_path = tmp > child->max_odd_path ? tmp : child->max_odd_path;
            }

            if (!post->hut && post->max_odd_path != 0) {
                int tmp = post->max_odd_path + post->val_of_routes[j];
                child->max_even_path = tmp > child->max_even_path ? tmp : child->max_even_path;
            }
        }
    }
}
