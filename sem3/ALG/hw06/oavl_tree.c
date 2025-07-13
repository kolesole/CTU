#include "oavl_tree.h"

bool insert_vertex(int key) {
    if (root == NULL) {
        if (!create_new_vertex(&root, key)) return false;

        num_of_vertices++;
        num_of_unmarked_vertices++;
        root->parent = NULL;

        return true;
    }

    vertex_t* tmp = root;
    vertex_t* new_vertex;
    while (1) {
        if (key == tmp->key && !tmp->is_marked) return true;

        if (key <= tmp->key) {
            if (tmp->left == NULL) {
                if (tmp->is_marked) {
                    tmp->key = key;
                    tmp->is_marked = false;
                    num_of_marked_vertices--;
                    num_of_unmarked_vertices++;
                    return true;
                }

                if (!create_new_vertex(&new_vertex, key)) return false;

                tmp->left = new_vertex;
                new_vertex->parent = tmp;

                break;
            }
            tmp = tmp->left;
        }
        else if (key > tmp->key) {
            if (tmp->right == NULL) {
                if (tmp->is_marked) {
                    tmp->key = key;
                    tmp->is_marked = false;
                    num_of_marked_vertices--;
                    num_of_unmarked_vertices++;
                    return true;
                }

                if (!create_new_vertex(&new_vertex, key)) return false;

                tmp->right = new_vertex;
                new_vertex->parent = tmp;

                break;
            }
            tmp = tmp->right;
        }
    }
    num_of_vertices++;
    num_of_unmarked_vertices++;

    int path[2] = {-1, -1};    // 0 - left, 1 - right
    while (new_vertex->parent != NULL) {
        if (new_vertex->parent->left == new_vertex) {
            new_vertex->parent->left_depth = new_vertex->depth + 1;
            new_vertex->parent->depth = new_vertex->parent->left_depth > new_vertex->parent->right_depth ? new_vertex->parent->left_depth : new_vertex->parent->right_depth;

            path[0] = path[1];
            path[1] = 0;
        }
        else if (new_vertex->parent->right == new_vertex) {
            new_vertex->parent->right_depth = new_vertex->depth + 1;
            new_vertex->parent->depth = new_vertex->parent->left_depth > new_vertex->parent->right_depth ? new_vertex->parent->left_depth : new_vertex->parent->right_depth;

            path[0] = path[1];
            path[1] = 1;
        }

        new_vertex = new_vertex->parent;
        bool ret = try_balance(new_vertex, path);
        try_move_down(ret ? new_vertex->parent : new_vertex);

        if (ret) return true;
    }

    return true;
}

void delete_vertex(int key) {
    vertex_t* tmp = root;
    while (tmp != NULL) {
        if (!tmp->is_marked && tmp->key == key) {
            tmp->is_marked = true;
            num_of_marked_vertices++;
            num_of_unmarked_vertices--;
            return;
        }
        else if (key > tmp->key) {
            tmp = tmp->right;
        }
        else if (key <= tmp->key) {
            tmp = tmp->left;
        }
    }
}

bool try_balance(vertex_t* vertex, int path[2]) {
    if (abs(vertex->left_depth - vertex->right_depth) <= 1) return false;

    if (path[0] == -1 || path[0] == path[1]) {
        path[1] == 0 ? right_rotation(vertex) : left_rotation(vertex);
        return true;
    }

    path[0] == 0 ? right_left_rotation(vertex) : left_right_rotation(vertex);

    return true;
}

void try_move_down(vertex_t* vertex) {
    if (!vertex->is_marked || went_down) return;

    went_down = true;

    if (vertex->left == NULL) return;

    vertex_t* max_left = vertex->left;
    while (max_left->right != NULL) {
        max_left = max_left->right;
    }

    if (max_left->is_marked) return;

    vertex->key = max_left->key;
    vertex->is_marked = false;
    max_left->is_marked = true;
}
