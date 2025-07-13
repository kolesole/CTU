#ifndef SORTING_H
#define SORTING_H

#include <stdbool.h>

#include "post.h"
#include "queue.h"

//function with topological sorting
bool topological_sort(post_t** post_array, post_t*** sorted_post_array, int num_of_posts);

#endif //SORTING_H
