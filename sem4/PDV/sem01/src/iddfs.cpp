#include "iddfs.h"
#include <atomic>

void iddfs_seq(state_ptr root, std::atomic<state_ptr>& goal, int cur_depth, int max_depth) {
    if (root->is_goal()) {
        goal.store(root);
        return;
    }

    if (cur_depth == max_depth) return;

    for (auto child : root->next_states()) {
        iddfs_seq(child, goal, cur_depth + 1, max_depth);
    }
}

void iddfs_par(std::atomic<state_ptr>& goal, std::atomic<uint64_t>& best_id, std::atomic<uint64_t>& lowest_cost,
               state_ptr root,  uint64_t cur_depth, uint64_t max_depth) {
    auto cur_id = root->get_identifier();
    auto cur_cost = root->current_cost();
    if (root->is_goal()) {
        while (true) {
            state_ptr old = goal.load();
            if (old == nullptr || cur_cost < lowest_cost
                || (cur_cost == lowest_cost && cur_id < best_id.load())) {
                if (goal.compare_exchange_weak(old, root)) {
                    best_id.store(cur_id);
                    lowest_cost.store(cur_cost);
                    break;
                }
            } else {
                break;
            }
        }
        return;
    }
    if (cur_cost >= lowest_cost.load()) return;

    if (cur_depth >= max_depth) {
        if (!goal.load()) {
            return;
        } else {
            max_depth++;
        }
    }

    auto predecessor = root->get_predecessor();
    for (auto child : root->next_states()) {
        if (child == nullptr || (predecessor && child->get_identifier() == predecessor->get_identifier())) continue;

        #pragma omp task shared(goal, best_id, lowest_cost)
        iddfs_par(goal, best_id, lowest_cost, child, cur_depth + 1, max_depth);
    }
}

state_ptr iddfs(state_ptr root) { // NOLINT(*-unnecessary-value-param)
    std::atomic<state_ptr> goal = nullptr;
    std::atomic<uint64_t> best_id = UINT64_MAX;
    std::atomic<uint64_t> lowest_cost = UINT64_MAX;
    uint64_t max_depth = 0;

    while (!goal.load()) {
        #pragma omp parallel
        {
            #pragma omp single
            iddfs_par(goal, best_id, lowest_cost, root, 0, max_depth);
        }
        max_depth++;
    }

    return goal.load();
}
