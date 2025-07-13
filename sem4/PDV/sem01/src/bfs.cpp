#include "bfs.h"

#include <queue>
#include <atomic>
#include <unordered_set>
#include <omp.h>

state_ptr bfs_seq(state_ptr root) { // NOLINT(*-unnecessary-value-param)
    std::queue<state_ptr> q = std::queue<state_ptr>();
    q.push(root);
    while (!q.empty()) {
        auto cur_state = q.front();
        q.pop();

        if (cur_state->is_goal()) return cur_state;

        for (auto child : cur_state->next_states()) {
            q.push(child);
        }
    }

    return nullptr;
}

state_ptr bfs_par(state_ptr root) {
    std::deque<state_ptr> cur_depth = std::deque<state_ptr>();
    cur_depth.push_back(root);

    std::unordered_set<uint64_t> visited = std::unordered_set<uint64_t>();
    // visited.insert(root->get_identifier());

    std::atomic<bool> flag = false;
    std::atomic<state_ptr> goal_state = nullptr;
    std::atomic<uint64_t> best_id;

    while (!cur_depth.empty() && !flag.load()) {
        size_t cur_depth_size = cur_depth.size();

        #pragma omp parallel // num_threads(8)
        {
            std::deque<state_ptr> local_next_depth = std::deque<state_ptr>();
            std::unordered_set<uint64_t> local_visited = std::unordered_set<uint64_t>();

            #pragma omp for schedule(static)
            for (size_t i = 0; i < cur_depth_size; i++) {
                auto cur_state = cur_depth[i];
                auto cur_id = cur_state->get_identifier();
                if (visited.contains(cur_id) || local_visited.contains(cur_id)) {
                    continue;
                }

                local_visited.insert(cur_id);
                // local_visited.insert(cur_id);

                if (cur_state->is_goal()) {
                    while (true) {
                        state_ptr old = goal_state.load();
                        if (old == nullptr || cur_id < best_id.load()) {
                            if (goal_state.compare_exchange_weak(old, cur_state)) {
                                best_id.store(cur_id);
                                flag.store(true);
                            }
                        } else {
                            break;
                        }
                    }
                }

                if (flag.load()) continue;

                for (auto child : cur_state->next_states()) {
                    if (flag.load()) break;
                    auto child_id = child->get_identifier();
                    if (visited.contains(child_id) || local_visited.contains(child_id)) {
                        continue;
                    }

                    local_next_depth.push_front(child);
                    // local_visited.insert(child_id);
                }
            }

            #pragma omp barrier

            if (!flag.load()) {
                #pragma omp single
                {
                    cur_depth = std::deque<state_ptr>();
                    visited = std::unordered_set<uint64_t>();
                }

                #pragma omp critical
                {
                    cur_depth.insert(cur_depth.end(), local_next_depth.begin(), local_next_depth.end());
                }

                #pragma omp critical
                {
                    visited.insert(local_visited.begin(), local_visited.end());
                }
            }
        }
    }

    return goal_state.load();
}

// Naimplementujte efektivni algoritmus pro nalezeni nejkratsi cesty v grafu. V teto metode nemusite prilis
// optimalizovat pametove naroky, a vhodnym algoritmem tak muze byt napriklad pouziti prohledavani do sirky
// (breadth-first search).
//
// Funkce ma za ukol vratit ukazatel na cilovy stav, ktery je dosazitelny pomoci nejkratsi cesty.
// Evaluacni kod muze funkci volat opakovane, dejte si pozor, abyste korektne reinicializovali
// globalni promenne, pokud je pouzivate (idealne se jim vyhnete).
state_ptr bfs(state_ptr root) { // NOLINT(*-unnecessary-value-param)
    return bfs_par(root);
}
