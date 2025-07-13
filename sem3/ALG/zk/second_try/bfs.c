#include "bfs.h"

bool bfs(grid_point** grid, int start_mouse_pos, int end_mouse_pos, int start_cat_pos, int num_of_cat_jmps) {
    node_t* head = NULL;
    node_t* tail = NULL;
    if (!push(&head, &tail, start_mouse_pos, start_cat_pos, 0, 0, num_of_cat_jmps, -1)) {
        return false;
    }

    bool end = false;
    while (head != NULL) {
        node_t* cur_node = pop(&head);
        int cur_mouse_pos = cur_node->mouse_pos;
        int cur_cat_pos = cur_node->cat_pos;
        int cur_path_len = cur_node->path_len;
        int cur_num_of_noisy_nodes = cur_node->num_of_noisy_nodes;
        int cur_num_of_cat_jmps = cur_node->num_of_cat_jmps;
        int cur_prev = cur_node->prev;
        free(cur_node);
        //printf("%d\n", cur_num_of_cat_jmps);
       // printf("%d %d\n", cur_mouse_pos, cur_cat_pos);
        //grid[cur_mouse_pos]->is_visited[cur_num_of_cat_jmps] = true;

        if (end) {
            if (cur_mouse_pos == end_mouse_pos) {
                //printf("%d %d\n", cur_path_len, cur_num_of_noisy_nodes);
                min_num_of_noisy_points = min_num_of_noisy_points < cur_num_of_noisy_nodes ? min_num_of_noisy_points : cur_num_of_noisy_nodes;
            }
            continue;
        }

        if (cur_mouse_pos == end_mouse_pos) {
            min_path_len = cur_path_len;
            min_num_of_noisy_points = cur_num_of_noisy_nodes;
            end = true;
            continue;
        }

        if (grid[cur_mouse_pos]->v < cur_num_of_noisy_nodes) continue;
        grid[cur_mouse_pos]->v = cur_num_of_noisy_nodes;

        //if (cur_prev == cur_mouse_pos) continue;

        //if (grid[cur_mouse_pos]->is_visited) continue;

        //grid[cur_mouse_pos]->is_visited = true;


        for (int i = 0; i < grid[cur_mouse_pos]->num_of_children; i++) {
            int new_mouse_pos = grid[cur_mouse_pos]->children[i];

            if (grid[new_mouse_pos]->v <= cur_num_of_noisy_nodes) continue;

            //if (grid[new_mouse_pos]->v[cur_num_of_noisy_nodes]) continue;

            if (grid[cur_mouse_pos]->is_visited[i] <= cur_num_of_noisy_nodes) {
                //grid[new_mouse_pos]->v = cur_num_of_noisy_nodes;
                break;
            }
            //grid[cur_mouse_pos]->is_visited[i] = cur_num_of_noisy_nodes;

            if (new_mouse_pos == cur_cat_pos) {
                grid[new_mouse_pos]->v = cur_num_of_noisy_nodes;
                continue;
            }

            //if (new_mouse_pos == cur_prev) continue;

            //if (grid[new_mouse_pos]->is_visited[cur_num_of_cat_jmps]) continue;

            if (grid[new_mouse_pos]->is_noisy && cur_num_of_cat_jmps > 0) {
                bool flag1 = false;
                for (int j = 0; j < grid[cur_cat_pos]->num_of_children; j++) {
                    if (new_mouse_pos == grid[cur_cat_pos]->children[j]) {
                        grid[new_mouse_pos]->v = cur_num_of_noisy_nodes + 1;
                        //grid[new_mouse_pos]->is_visited[cur_num_of_cat_jmps - 1] = true;
                        //grid[new_mouse_pos]->is_visited = true;
                        flag1 = true;
                        //break;
                    }
                }

                if (flag1) continue;
            }

            int new_num_of_noisy_nodes = cur_num_of_noisy_nodes + (grid[new_mouse_pos]->is_noisy ? 1 : 0);

            if (!push(&head, &tail, new_mouse_pos, cur_cat_pos, cur_path_len + 1, new_num_of_noisy_nodes, cur_num_of_cat_jmps, cur_mouse_pos)) {
                delete_queue(head);
                return false;
            }

            //grid[new_mouse_pos]->v = new_num_of_noisy_nodes;

            if (grid[new_mouse_pos]->is_noisy && cur_num_of_cat_jmps > 0) {
                for (int j = 0; j < grid[cur_cat_pos]->num_of_children; j++) {
                    if (!push(&head, &tail, new_mouse_pos, grid[cur_cat_pos]->children[j], cur_path_len + 1, new_num_of_noisy_nodes, cur_num_of_cat_jmps - 1, cur_mouse_pos)) {
                        delete_queue(head);
                        return false;
                    }

                    //grid[new_mouse_pos]->is_visited[grid[cur_cat_pos]->children[j]][cur_num_of_cat_jmps - 1] = true;
                }
            }
        }
    }

    return true;
}
