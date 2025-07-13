#ifndef ROTATION_H
#define ROTATION_H

#include "oavl_utils.h"

extern vertex_t* root;

// function for L rotation
void left_rotation(vertex_t* vertex);
// function for R rotation
void right_rotation(vertex_t* vertex);
// function for LR rotation
void left_right_rotation(vertex_t* vertex);
// function for RL rotation
void right_left_rotation(vertex_t* vertex);

#endif //ROTATION_H
