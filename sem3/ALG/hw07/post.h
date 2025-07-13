#ifndef POST_H
#define POST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//structure to represent post
typedef struct post_t {
    int indx;
    bool hut;
    int max_even_path;
    int max_odd_path;
    int num_of_parents;
    int num_of_children;
    int size_of_children;
    struct post_t** children;
    int* val_of_routes;
} post_t;

//function to allocate memory and fill up information about post
bool post_init(post_t** post, int indx);
//function to reallocate memory for post
bool post_realloc(post_t** post);
//function to free memory for post
void post_free(post_t* post);
//function to mark all posts with hut
void mark_posts_with_hut(post_t** sorted_post_array, int num_of_posts, int* num_of_huts);

#endif //POST_H
