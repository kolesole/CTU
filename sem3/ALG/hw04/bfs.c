#include "bfs.h"

bool bfs(int rows, int cols, aux_point_t** aux_matrix, int max_speed, int* min_path) {
    node_t* head = NULL;
    node_t* tail = NULL;
    if (!push(&head, &tail, rows - 1, 0, 0, -1, 0)) {
        return false;
    }

    while (head != NULL) {
        node_t* cur_node = pop(&head);
        int cur_row = cur_node->row;
        int cur_col = cur_node->col;
        int cur_speed = cur_node->speed;
        int cur_direction = cur_node->direction;
        int path_length = cur_node->path_length;

        if (cur_row == 0 && cur_col == cols - 1) {
            *min_path = cur_node->path_length;
            free(cur_node);
            delete_queue(head);
            return true;
        }

        free(cur_node);

        if (cur_speed > 1) {
            int speed1 = cur_speed - 1;
            int speed2 = cur_speed;
            int speed3 = cur_speed + 1;

            int row1 = cur_row + (2 * speed1) * directions[cur_direction][0];
            int col1 = cur_col + (2 * speed1) * directions[cur_direction][1];
            int row2 = cur_row + (2 * speed2) * directions[cur_direction][0];
            int col2 = cur_col + (2 * speed2) * directions[cur_direction][1];
            int row3 = cur_row + (2 * speed3) * directions[cur_direction][0];
            int col3 = cur_col + (2 * speed3) * directions[cur_direction][1];

            if (row1 >= 0 && row1 < rows && col1 >= 0 && col1 < cols) {
                if (aux_matrix[row1][col1].is_visited[cur_direction][speed1 - 1] == 0) {
                    if (jmp_is_possible(rows, cols, cur_row, cur_col, row1, col1, speed1, cur_direction, aux_matrix)) {
                        aux_matrix[row1][col1].is_visited[cur_direction][speed1 - 1]++;
                        push(&head, &tail, row1, col1, speed1, cur_direction, path_length + 1);
                    }
                }
            }

            if (row2 >= 0 && row2 < rows && col2 >= 0 && col2 < cols) {
                if (aux_matrix[row2][col2].is_visited[cur_direction][speed2 - 1] == 0) {
                    if (jmp_is_possible(rows, cols, cur_row, cur_col, row2, col2, speed2, cur_direction, aux_matrix)) {
                        aux_matrix[row2][col2].is_visited[cur_direction][speed2 - 1]++;
                        push(&head, &tail, row2, col2, speed2, cur_direction, path_length + 1);
                    }
                }
            }

            if (row3 >= 0 && row3 < rows && col3 >= 0 && col3 < cols && speed3 <= max_speed) {
                if (aux_matrix[row3][col3].is_visited[cur_direction][speed3 - 1] == 0) {
                    if (jmp_is_possible(rows, cols, cur_row, cur_col, row3, col3, speed3, cur_direction, aux_matrix)) {
                        aux_matrix[row3][col3].is_visited[cur_direction][speed3 - 1]++;
                        push(&head, &tail, row3, col3, speed3, cur_direction, path_length + 1);
                    }
                }
            }
            continue;
        }

        for (int direction = 0; direction < 4; direction++) {
            if (direction == cur_direction) {
                int speed1 = 1;
                int speed2 = 2;

                int row1 = cur_row + (2 * speed1) * directions[direction][0];
                int col1 = cur_col + (2 * speed1) * directions[direction][1];
                int row2 = cur_row + (2 * speed2) * directions[direction][0];
                int col2 = cur_col + (2 * speed2) * directions[direction][1];

                if (row1 >= 0 && row1 < rows && col1 >= 0 && col1 < cols) {
                    if (aux_matrix[row1][col1].is_visited[direction][speed1 - 1] == 0) {
                        if (jmp_is_possible(rows, cols, cur_row, cur_col, row1, col1, speed1, direction, aux_matrix)) {
                            aux_matrix[row1][col1].is_visited[direction][speed1 - 1]++;
                            push(&head, &tail, row1, col1, speed1, direction, path_length + 1);
                        }
                    }
                }

                if (row2 >= 0 && row2 < rows && col2 >= 0 && col2 < cols && speed2 <= max_speed) {
                    if (aux_matrix[row2][col2].is_visited[direction][speed2 - 1] == 0) {
                        if (jmp_is_possible(rows, cols, cur_row, cur_col, row2, col2, speed2, direction, aux_matrix)) {
                            aux_matrix[row2][col2].is_visited[direction][speed2 - 1]++;
                            push(&head, &tail, row2, col2, speed2, direction, path_length + 1);
                        }
                    }
                }

                continue;
            }

            int speed = 1;
            int row = cur_row + (2 * speed) * directions[direction][0];
            int col = cur_col + (2 * speed) * directions[direction][1];

            if (row >= 0 && row < rows && col >= 0 && col < cols) {
                if (aux_matrix[row][col].is_visited[direction][speed - 1] == 0) {
                    if (jmp_is_possible(rows, cols, cur_row, cur_col, row, col, speed, direction, aux_matrix)) {
                        aux_matrix[row][col].is_visited[direction][speed - 1]++;
                        push(&head, &tail, row, col, speed, direction, path_length + 1);
                    }
                }
            }
        }
    }

    return false;
}

bool jmp_is_possible(int rows, int cols, int point1_row, int point1_col, int point2_row, int point2_col, int speed, int direction, aux_point_t** aux_matrix) {
    if (point1_row < 0 || point1_row >= rows || point1_col < 0 || point1_col >= cols ||
        point2_row < 0 || point2_row >= rows || point2_col < 0 || point2_col >= cols) return false;

    int i = 1;
    while (point1_row != point2_row || point1_col != point2_col) {
        int max = i - 1 < 2 * speed + 1 - i ? i - 1 : 2 * speed + 1 - i;

        if (aux_matrix[point1_row][point1_col].elevation > max) return false;

        point1_row += directions[direction][0];
        point1_col += directions[direction][1];
        i++;
    }

    return true;
}
