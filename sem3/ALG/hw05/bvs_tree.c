#include "bvs_tree.h"

bool create_new_node(node_t** node, int num) {
    *node = (node_t*)malloc(sizeof(node_t));
    if (*node == NULL) {
        fprintf(stderr, "ERROR: cannot allocate memory for node!\n");
        return false;
    }

    (*node)->num = num;
    (*node)->is_deleted = false;
    (*node)->left = NULL;
    (*node)->right = NULL;

    return true;
}

void free_tree(node_t* root) {
    if (root == NULL) return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void insert_node(node_t** root, node_t* new_node) {
    new_node->left = NULL;
    new_node->right = NULL;

    if (*root == NULL) {
        num_of_undel_nodes++;
        *root = new_node;
        return;
    }

    int new_depth = 0;
    node_t* tmp = *root;
    node_t* parent = NULL;
    while (tmp != NULL) {
        if (tmp->num == new_node->num) {
            if (tmp->is_deleted) {
                num_of_del_nodes--;
                depth_of_del_nodes -= new_depth;
                num_of_undel_nodes++;
                depth_of_undel_nodes += new_depth;
                tmp->is_deleted = false;
            }

            free(new_node);
            return;
        }

        parent = tmp;
        if (new_node->num < tmp->num) {
            tmp = tmp->left;
        } else {
            tmp = tmp->right;
        }
        new_depth++;
    }

    if (new_node->num < parent->num) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    num_of_undel_nodes++;
    depth_of_undel_nodes += new_depth;
    cur_depth = cur_depth > new_depth ? cur_depth : new_depth;
}

void delete_node(node_t* root, int num) {
    int new_depth = 0;
    node_t* tmp = root;
    while (tmp != NULL) {
        if (tmp->num == num) {
            if (!tmp->is_deleted) {
                num_of_del_nodes++;
                depth_of_del_nodes += new_depth;
                num_of_undel_nodes--;
                depth_of_undel_nodes -= new_depth;
                tmp->is_deleted = true;
            }

            return;
        }

        tmp = num < tmp->num ? tmp->left : tmp->right;

        new_depth++;
    }
}

void compact_tree(node_t* root, node_t** new_root) {
    num_of_del_nodes = 0;
    depth_of_del_nodes = 0;
    num_of_undel_nodes = 0;
    depth_of_undel_nodes = 0;
    cur_depth = 0;

    dfs(root, new_root);
}

void dfs(node_t* root, node_t** new_root) {
    if (root == NULL) return;

    node_t* left = root->left;
    node_t* right = root->right;
    if (!root->is_deleted) {
        insert_node(new_root, root);
    }

    dfs(left, new_root);
    dfs(right, new_root);

    if (root->is_deleted) {
        free(root);
    }
}
