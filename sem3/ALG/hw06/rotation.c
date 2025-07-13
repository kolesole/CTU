#include "rotation.h"

void left_rotation(vertex_t* vertex) {
    vertex_t* right_vertex = vertex->right;
    vertex_t* right_left_vertex = right_vertex->left;

    right_vertex->left = vertex;
    vertex->right = right_left_vertex;

    vertex_t* vertex_parent = vertex->parent;
    vertex->parent = right_vertex;
    right_vertex->parent = vertex_parent;

    if (vertex_parent == NULL) {
        root = right_vertex;
    } else {
        if (vertex_parent->left == vertex) {
            vertex_parent->left = right_vertex;
        } else {
            vertex_parent->right = right_vertex;
        }
    }

    if (right_left_vertex) {
        right_left_vertex->parent = vertex;
    }

    vertex->right_depth = right_left_vertex ? right_left_vertex->depth + 1 : 0;
    vertex->depth = vertex->left_depth > vertex->right_depth ? vertex->left_depth : vertex->right_depth;

    right_vertex->left_depth = vertex->depth + 1;
    right_vertex->depth = right_vertex->left_depth > right_vertex->right_depth ? right_vertex->left_depth : right_vertex->right_depth;
}

void right_rotation(vertex_t* vertex) {
    vertex_t* left_vertex = vertex->left;
    vertex_t* left_right_vertex = left_vertex->right;

    left_vertex->right = vertex;
    vertex->left = left_right_vertex;

    vertex_t* vertex_parent = vertex->parent;
    vertex->parent = left_vertex;
    left_vertex->parent = vertex_parent;

    if (vertex_parent == NULL) {
        root = left_vertex;
    } else {
        if (vertex_parent->left == vertex) {
            vertex_parent->left = left_vertex;
        } else {
            vertex_parent->right = left_vertex;
        }
    }

    if (left_right_vertex) {
        left_right_vertex->parent = vertex;
    }

    vertex->left_depth = left_right_vertex ? left_right_vertex->depth + 1 : 0;
    vertex->depth = vertex->left_depth > vertex->right_depth ? vertex->left_depth : vertex->right_depth;

    left_vertex->right_depth = vertex->depth + 1;
    left_vertex->depth = left_vertex->left_depth > left_vertex->right_depth ? left_vertex->left_depth : left_vertex->right_depth;
}

void left_right_rotation(vertex_t* vertex) {
    left_rotation(vertex->left);
    right_rotation(vertex);
}

void right_left_rotation(vertex_t* vertex) {
    right_rotation(vertex->right);
    left_rotation(vertex);
}
