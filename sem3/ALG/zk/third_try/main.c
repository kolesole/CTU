#include <stdio.h>

#include "backtracking.h"
#include "tree_utils.h"
#include "utils.h"
#include "sorting.h"

int max_score = 0;
int cur_sum = 0;

int main() {
    int N, M;
    int A, B;
    node_t** tree;

    if (!read_input(&N, &M, &A, &B, &tree)) return -1;

    sorted_node_t* sorted_tree;
    if (!sort(&sorted_tree, tree, N)) {
        my_free_tree(N, tree);
        return -1;
    }

    backtracking(sorted_tree, tree, 0, N, A, B);
    printf("%d\n", max_score);

    my_free_sorted_tree(sorted_tree);
    my_free_tree(N, tree);
    return 0;
}
