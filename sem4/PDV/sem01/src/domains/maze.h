#pragma once

#include <sstream>
#include <cmath>
#include <random>
#include <iostream>
#include <utility>
#include "../state.h"

// NOTE: this code is very non-idiomatic from a performance perspective; however, making the domain faster
//  would make it much harder for you to get a reasonable speedup over the serial solution

/// A domain of WIDTH*HEIGHT 2D maze with a fixed starting and goal position. The state corresponds to a position
/// in the maze, each action corresponds to moving in the selected direction, unless blocked by a wall.
template<size_t WIDTH, size_t HEIGHT, std::mt19937::result_type SEED, bool UNIFORM>
class maze {
    static_assert(WIDTH % 2 == 1, "Sirka bludiste musi byt licha");
    static_assert(HEIGHT % 2 == 1, "Vyska bludiste musi byt licha");

    static constexpr float COMPLEXITY = 0.9;
    static constexpr float DENSITY = 0.75;

private:
    std::vector<bool> m_maze;
    std::vector<size_t> m_start;
    std::vector<size_t> m_goal;

public:
    maze() {
        m_start = std::vector<size_t>{1, 1};
        m_goal = std::vector<size_t>{HEIGHT - 2, WIDTH - 2};

        generate_maze(SEED);

        for (int i = 0; i < 10; i++) {
            if (m_maze[m_start[0] * WIDTH + m_start[1]] || m_maze[m_goal[0] * WIDTH + m_goal[1]]) {
                std::cerr << "Spatne vygenerovane bludiste #" << i << ". Generuji znovu...\n";
                m_goal[0]--;
                m_goal[1]--;
                generate_maze(SEED + 1 + i);
            } else break;
        }

        if (m_maze[m_start[0] * WIDTH + m_start[1]] || m_maze[m_goal[0] * WIDTH + m_goal[1]]) {
            throw std::runtime_error("Could not generate a valid maze after 10 attempts. "
                                     "Change the domain parameters and try again.\n");
        }
    }

    [[nodiscard]] state_ptr get_root() const {
        return std::make_shared<dstate>(state_ptr(), 0, m_start, &m_maze, &m_goal);
    }

    friend std::ostream& operator<<(std::ostream& s, const maze& d) {
        s << "Domain: 2D Maze\n";
        s << "Width = " << WIDTH << ", height = " << HEIGHT << ", uniform costs = " << (UNIFORM ? "yes" : "no")
          << ", seed = " << SEED << "\n";
        s << "Map = ";

        if (WIDTH >= 64 && HEIGHT >= 64) {
            s << "<skipped, maze is too large to render>\n";
            return s;
        }

        s << "\n";

        for (size_t i = 0; i < HEIGHT; i++) {
            for (size_t j = 0; j < WIDTH; j++) {
                if (i == d.m_start[0] && j == d.m_start[1]) {
                    s << "S";
                    continue;
                }
                if (i == d.m_goal[0] && j == d.m_goal[1]) {
                    s << "G";
                    continue;
                }
                s << (d.m_maze[i * WIDTH + j] ? "X" : " ");
            }
            s << "\n";
        }
        return s;
    }

private:
    void generate_maze(std::mt19937::result_type seed) {
        std::mt19937 rng(seed);

        size_t shape[2] = {(WIDTH / 2) * 2 + 1, (HEIGHT / 2) * 2 + 1};
        // Adjust complexity and density relative to maze size
        auto complexity = (size_t) (COMPLEXITY * (float) (5 * (shape[0] + shape[1])));
        auto density = (size_t) (DENSITY * (float) ((shape[0] / 2) * (shape[1] / 2)));
        // Build actual maze
        m_maze = std::vector<bool>(WIDTH * HEIGHT);
        // Fill borders
        for (size_t i = 0; i < WIDTH; i++) {
            m_maze[i] = true;
            m_maze[WIDTH * (HEIGHT - 1) + i] = true;
        }
        for (size_t j = 0; j < HEIGHT; j++) {
            m_maze[j * WIDTH] = true;
            m_maze[j * WIDTH + WIDTH - 1] = true;
        }

        // Make aisles
        std::uniform_int_distribution<size_t> uniX(0, shape[1] / 2);
        std::uniform_int_distribution<size_t> uniY(0, shape[0] / 2);
        for (size_t i = 0; i < density; i++) {
            size_t x = 2 * uniX(rng);
            size_t y = 2 * uniY(rng);
            m_maze[x * WIDTH + y] = true;
            for (size_t j = 0; j < complexity; j++) {
                std::vector<size_t> neighbours;
                if (x > 1) {
                    neighbours.push_back(y);
                    neighbours.push_back(x - 2);
                }
                if (x < shape[1] - 2) {
                    neighbours.push_back(y);
                    neighbours.push_back(x + 2);
                }
                if (y > 1) {
                    neighbours.push_back(y - 2);
                    neighbours.push_back(x);
                }
                if (y < shape[0] - 2) {
                    neighbours.push_back(y + 2);
                    neighbours.push_back(x);
                }
                if (!neighbours.empty()) {
                    std::uniform_int_distribution<int> uni(0, (int) (neighbours.size() / 2) - 1);
                    int ridx = uni(rng);
                    auto y_ = neighbours[2 * ridx];
                    auto x_ = neighbours[2 * ridx + 1];
                    if (!m_maze[x_ * WIDTH + y_]) {
                        m_maze[x_ * WIDTH + y_] = true;
                        m_maze[(x_ + (int) ((x - x_) / 2)) * WIDTH + y_ + (int) ((y - y_) / 2)] = true;
                        x = x_;
                        y = y_;
                    }
                }
            }
        }
    }

private:
    class dstate final : public state, public std::enable_shared_from_this<dstate> {
    private:
        std::vector<size_t> m_position;
        uint64_t m_id;

        const std::vector<bool>* m_maze;
        const std::vector<size_t>* m_goal;

    public:
        dstate(state_ptr predecessor, uint64_t cost, std::vector<size_t> conf,
               const std::vector<bool>* maze, const std::vector<size_t>* goal)
            : state(std::move(predecessor), cost), m_position(conf), m_maze(maze), m_goal(goal) {
            m_id = conf[0] * WIDTH + conf[1];
        }

        [[nodiscard]] std::vector<state_ptr> next_states() const override {
            auto new_position = m_position;
            std::vector<state_ptr> succ;

            uint64_t cost = UNIFORM ? 1 : (m_id % 5);
            if (!((*m_maze)[(m_position[0] - 1) * WIDTH + m_position[1]])) {
                new_position[0] = m_position[0] - 1;
                succ.emplace_back(std::make_shared<dstate>(
                    this->shared_from_this(), current_cost() + cost, new_position, m_maze, m_goal));
                new_position[0] = m_position[0];
            }

            if (!((*m_maze)[(m_position[0] + 1) * WIDTH + m_position[1]])) {
                new_position[0] = m_position[0] + 1;
                succ.emplace_back(std::make_shared<dstate>(
                    this->shared_from_this(), current_cost() + cost, new_position, m_maze, m_goal));
                new_position[0] = m_position[0];
            }

            if (!((*m_maze)[(m_position[0]) * WIDTH + m_position[1] - 1])) {
                new_position[1] = m_position[1] - 1;
                succ.emplace_back(std::make_shared<dstate>(
                    this->shared_from_this(), current_cost() + cost, new_position, m_maze, m_goal));
                new_position[1] = m_position[1];
            }

            if (!((*m_maze)[(m_position[0]) * WIDTH + m_position[1] + 1])) {
                new_position[1] = m_position[1] + 1;
                succ.emplace_back(std::make_shared<dstate>(
                    this->shared_from_this(), current_cost() + cost, new_position, m_maze, m_goal));
                new_position[1] = m_position[1];
            }

            return succ;
        }

        [[nodiscard]] bool is_goal() const override {
            return m_position[0] == (*m_goal)[0] && m_position[1] == (*m_goal)[1];
        }

        [[nodiscard]] uint64_t get_identifier() const override {
            return m_id;
        }

        [[nodiscard]] std::string to_string() const override {
            std::ostringstream out;
            out << "[ " << m_position[0] << ", " << m_position[1] << " ]";
            return out.str();
        }
    };
};

// explicit instantiation to get type checking
template
class maze<1, 1, 0, true>;

// verify that we implement the `domain` "interface"
static_assert(domain<maze<1, 1, 0, true>>);
