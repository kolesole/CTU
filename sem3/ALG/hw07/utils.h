#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "post.h"

//function to allocate memory and fill up array with posts
bool post_array_init(post_t*** post_array, int num_of_posts);
//function to free memory for array with posts
void post_array_free(post_t** post_array, int num_of_posts);
//function to read input
bool read_input(post_t*** post_array, int* num_of_posts, int* num_of_routes);

#endif //UTILS_H
