#include "utils.h"

bool read_input(int* N, int* M, int* A, int* B, node_t*** tree) {
    if (scanf("%d %d %d %d", N, M, A, B) != 4) {
        fprintf(stderr, "ERROR: Wrong input!\n");
        return false;
    }

    if (!my_malloc_tree(*N, tree)) return false;

    for (int i = 0; i < *M; i++) {
        int first_node, second_node;
        if (scanf("%d %d", &first_node, &second_node) != 2) {
            fprintf(stderr, "ERROR: Wrong input!\n");
            my_free_tree(*N, *tree);
            return false;
        }

        first_node--;
        second_node--;

        if ((*tree)[first_node]->num_of_children == (*tree)[first_node]->size_of_children) {
            if (!my_realloc_node(&((*tree)[first_node]), (*tree)[first_node]->size_of_children * 2)) {
                my_free_tree(*N, *tree);
                return false;
            }
        }

        if ((*tree)[second_node]->num_of_children == (*tree)[second_node]->size_of_children) {
            if (!my_realloc_node(&((*tree)[second_node]), (*tree)[second_node]->size_of_children * 2)) {
                my_free_tree(*N, *tree);
                return false;
            }
        }

        (*tree)[first_node]->children[(*tree)[first_node]->num_of_children++] = second_node;
        (*tree)[second_node]->children[(*tree)[second_node]->num_of_children++] = first_node;
        (*tree)[first_node]->num_of_unmarked_children++;
        (*tree)[second_node]->num_of_unmarked_children++;
    }

    return true;
}
