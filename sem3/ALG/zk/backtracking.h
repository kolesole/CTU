#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "sorting.h"
#include "tree_utils.h"

extern int max_score;
extern int cur_sum;

void backtracking(sorted_node_t* sorted_tree, node_t** tree, int indx, int N, int A, int B);
int find_score(node_t** tree, int indx);
int find_score_for_tree(node_t** tree, int N);
void find_cur_score(node_t** tree, int indx, int prev_Colour);
//int find_child_score(node_t** tree, int indx);

#endif //BACKTRACKING_H
