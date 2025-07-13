#include "backtracking.h"

void backtracking(sorted_node_t* sorted_tree, node_t** tree, int indx, int N, int A, int B) {
    if (indx >= N) return;

    //int max_score = 0;

    int indx_in_tree = sorted_tree[indx].indx;

    //int max_possible = 0;

    int prev_colour = -1;

    for (int i = 2; i >= 0; i--) {
        int new_A = A;
        int new_B = B;

        if (i == 1) {
            if (new_A <= 0) continue;
            new_A--;
        }

        if (i == 2) {
            if (new_B <= 0) continue;
            new_B--;
        }

        tree[indx_in_tree]->colour = i;

        find_cur_score(tree, indx_in_tree, prev_colour);

        prev_colour = tree[indx_in_tree]->colour;

        if (new_A + new_B > N - indx) continue;

        if (indx == N - 1) {
            int cur_score = cur_sum;
            max_score = cur_score > max_score ? cur_score : max_score;
            continue;
        }

        int tmp_score = cur_sum;
        int tmp_A = new_A;
        int tmp_B = new_B;
        for (int j = indx + 1; j < N; j++) {
            if (tmp_A + tmp_B > N - j) break;

            int ind_in_tree = sorted_tree[j].indx;
            if (tmp_A <= 0 && tmp_B <= 0) {
                tmp_score += tree[ind_in_tree]->num_of_children - tree[ind_in_tree]->num_of_unmarked_children;
            }
            else if (tmp_A > 0 && tmp_B <= 0) {
                tmp_score += (tree[ind_in_tree]->num_of_children - tree[ind_in_tree]->num_of_unmarked_children) + tmp_A;
                tmp_A--;
            }
            else if (tmp_B > 0 && tmp_A <= 0) {
                tmp_score += tree[ind_in_tree]->num_of_children;
                tmp_B--;
            }
            else if (tmp_A > 0 && tree[ind_in_tree]->num_of_children - tree[ind_in_tree]->num_of_unmarked_children > tree[ind_in_tree]->num_of_unmarked_children) {
                tmp_score += (tree[ind_in_tree]->num_of_children - tree[ind_in_tree]->num_of_unmarked_children) + tmp_A;
                tmp_A--;
            }
            else {
                tmp_score += tree[ind_in_tree]->num_of_children;
                tmp_B--;
            }
        }

        if (tmp_B != 0 || tmp_A != 0) continue;

        if (tmp_score > 0 && tmp_score <= max_score) {
            continue;
        }

        backtracking(sorted_tree, tree, indx + 1, N, new_A, new_B);
    }

    tree[indx_in_tree]->colour = -1;
    find_cur_score(tree, indx_in_tree, prev_colour);
}

void find_cur_score(node_t** tree, int indx, int prev_colour) {
    int colour = tree[indx]->colour;

    for (int i = 0; i < tree[indx]->num_of_children; i++) {
        int child_indx = tree[indx]->children[i];
        int child_colour = tree[child_indx]->colour;

        if (colour != -1 && prev_colour == -1) {
            tree[child_indx]->num_of_unmarked_children--;
        }

        if (colour == -1 && prev_colour != -1) {
            tree[child_indx]->num_of_unmarked_children++;
        }

        if (child_colour == -1) continue;

        if (prev_colour == 2) {
            if (child_colour == 0) {
                tree[indx]->cur_score--;
                cur_sum--;
            }

            if (child_colour == 1) {
                tree[child_indx]->cur_score--;
                cur_sum--;
            }
        }

        if (prev_colour == 1) {
            if (child_colour == 1) {
                tree[indx]->cur_score--;
                tree[child_indx]->cur_score--;
                cur_sum -= 2;
            }

            if (child_colour == 2) {
                tree[indx]->cur_score--;
                cur_sum--;
            }
        }

        if (prev_colour == 0) {
            if (child_colour == 2) {
                tree[child_indx]->cur_score--;
                cur_sum--;
            }
        }

        if (colour == 2) {
            if (child_colour == 0) {
                tree[indx]->cur_score++;
                cur_sum++;
            }

            if (child_colour == 1) {
                tree[child_indx]->cur_score++;
                cur_sum++;
            }
        }

        if (colour == 1) {
            if (child_colour == 1) {
                tree[indx]->cur_score++;
                tree[child_indx]->cur_score++;
                cur_sum += 2;
            }

            if (child_colour == 2) {
                tree[indx]->cur_score++;
                cur_sum++;
            }
        }

        if (colour == 0) {
            if (child_colour == 2) {
                tree[child_indx]->cur_score++;
                cur_sum++;
            }
        }
    }
}

int best_possible_score() {
    int score = 0;
    return score;
}

int find_score(node_t** tree, int indx) {
    int colour = tree[indx]->colour;

    if (colour == 0) return 0;

    int score = 0;
    for (int i = 0; i < tree[indx]->num_of_children; i++) {
        int child_colour = tree[tree[indx]->children[i]]->colour;

        if (child_colour == -1) continue;

        switch (colour) {
            case 1:
                score += (child_colour != 0) ? 1 : 0;
                break;
            case 2:
                score += (child_colour == 0) ? 1 : 0;
                break;
            default:
                break;
        }
    }

    return score;
}

int find_score_for_tree(node_t** tree, int N) {
    int score = 0;
    for (int i = 0; i < N; i++) {
        score += find_score(tree, i);
    }

    /*for (int i = 0; i < N; i++) {
        int colour = tree[i]->colour;
        for (int j = 0; j < tree[i]->num_of_children; j++) {
            int indx = tree[i]->children[j];

            if (i > indx) continue;

            int children_colour = tree[indx]->colour;

            if (colour == 1) {
                if (children_colour == 1) {
                    score += 2;
                    continue;
                }

                if (children_colour == 2) {
                    score += 1;
                    continue;
                }
            }

            if (colour == 0 && children_colour == 1) {
                score += 1;
                continue;
            }

            if (colour == 2) {
                if (children_colour == 0) {
                    score += 1;
                    continue;
                }

                if (children_colour == 1) {
                    score += 1;
                    continue;
                }
            }
        }
    }*/

    return score;
}

/*int find_child_score(node_t** tree, int indx) {
    int colour = tree[indx]->colour;

    int child_score = 0;
    for (int i = 0; i < tree[indx]->num_of_children; i++) {
        int child_colour = tree[tree[indx]->children[i]]->colour;
        switch (colour) {
            case 0:
                child_score += (child_colour == 2) ? 1 : 0;
                break;
            default:
                child_score += (child_colour == 1) ? 1 : 0;
                break;
        }
    }

    return child_score;
}*/

