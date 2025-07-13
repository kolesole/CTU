#pragma once

#include <sstream>
#include <cmath>
#include <random>
#include <utility>
#include "../state.h"

// NOTE: this code is very non-idiomatic from a performance perspective; however, making the domain faster
//  would make it much harder for you to get a reasonable speedup over the serial solution

/// Domain of the sliding puzzle game, where you have a square board with a single empty square, and your goal is to
/// get the numbered boxes in the remaining squares into the correct order. Each action corresponds to moving all
/// squares that are able to move in a selected direction.
template<size_t SIZE, size_t SOLUTION_DEPTH, std::mt19937::result_type SEED>
class sliding_puzzle {
    std::vector<size_t> m_starting_state{};
public:
    sliding_puzzle() {
        auto starting_state = std::vector<size_t>(SIZE * SIZE);
        for (size_t i = 0; i < SIZE; i++) {
            for (size_t k = 0; k < SIZE; k++) {
                starting_state[i * SIZE + k] = i * SIZE + k;
            }
        }

        // do SOLUTION_DEPTH random moves from the solved position
        std::mt19937 rng(SEED); // NOLINT(*-msc51-cpp)
        std::uniform_int_distribution<int> uni(0, 3);
        state_ptr s = std::make_shared<const dstate>(state_ptr(), 0, starting_state);
        for (size_t i = 0; i < SOLUTION_DEPTH; i++) {
            auto next_states = s->next_states();
            s = next_states[uni(rng) % next_states.size()];
        }

        auto ss = std::static_pointer_cast<const dstate>(s);
        m_starting_state = ss->get_conf();
    }

    [[nodiscard]] state_ptr get_root() const {
        return std::make_shared<const dstate>(state_ptr(), 0, m_starting_state);
    }

    friend std::ostream& operator<<(std::ostream& s, const sliding_puzzle& d) {
        s << "Domain: Sliding puzzle\n";
        s << "Size = " << SIZE << "*" << SIZE << ", seed = " << SEED << "\n";
        // not very efficient, but whatever
        s << "Initial layout = " << d.get_root()->to_string() << "\n";
        return s;
    }

private:
    class dstate final : public state, public std::enable_shared_from_this<dstate> {
    private:
        std::vector<size_t> m_conf;
        uint64_t m_id;

        const size_t BLANK = SIZE * SIZE - 1;

    public:
        dstate(state_ptr predecessor, uint64_t cost, std::vector<size_t> conf)
            : state(std::move(predecessor), cost), m_conf(std::move(conf)) {
            m_id = 0ull;
            uint64_t id2 = 0ull;
            uint64_t mult = 1;
            for (size_t i = 0; i < SIZE; i++) {
                for (size_t j = 0; j < SIZE; j++) {
                    m_id += mult * m_conf[i * SIZE + j];
                    id2 += pow(BLANK + 1, i * SIZE + j) * m_conf[i * SIZE + j];
                    mult *= BLANK + 1;
                }
            }

            auto vmin = std::min<uint64_t>(m_id, id2);
            m_id = std::max<uint64_t>(vmin, m_id);
        }


        [[nodiscard]] std::vector<state_ptr> next_states() const override {
            auto tmp_conf = m_conf;
            std::vector<state_ptr> succ;

            int blank_x = 0;
            int blank_y = 0;

            // find blank
            for (size_t i = 0; i < SIZE; i++) {
                for (size_t k = 0; k < SIZE; k++) {
                    if (m_conf[i * SIZE + k] == BLANK) {
                        blank_x = (int) i;
                        blank_y = (int) k;
                    }
                }
            }

            // 4 possibilities
            if (blank_x - 1 >= 0) {
                tmp_conf[blank_x * SIZE + blank_y] = m_conf[(blank_x - 1) * SIZE + blank_y];
                tmp_conf[(blank_x - 1) * SIZE + blank_y] = BLANK;
                succ.emplace_back(std::make_shared<dstate>(
                    this->shared_from_this(), current_cost() + 1, tmp_conf));
                tmp_conf[blank_x * SIZE + blank_y] = m_conf[blank_x * SIZE + blank_y];
                tmp_conf[(blank_x - 1) * SIZE + blank_y] = m_conf[(blank_x - 1) * SIZE + blank_y];
            }

            if (blank_x + 1 < (int) SIZE) {
                tmp_conf[blank_x * SIZE + blank_y] = m_conf[(blank_x + 1) * SIZE + blank_y];
                tmp_conf[(blank_x + 1) * SIZE + blank_y] = BLANK;
                succ.emplace_back(std::make_shared<dstate>(
                    this->shared_from_this(), current_cost() + 1, tmp_conf));
                tmp_conf[blank_x * SIZE + blank_y] = m_conf[blank_x * SIZE + blank_y];
                tmp_conf[(blank_x + 1) * SIZE + blank_y] = m_conf[(blank_x + 1) * SIZE + blank_y];
            }

            if (blank_y - 1 >= 0) {
                tmp_conf[blank_x * SIZE + blank_y] = m_conf[blank_x * SIZE + blank_y - 1];
                tmp_conf[blank_x * SIZE + blank_y - 1] = BLANK;
                succ.emplace_back(std::make_shared<dstate>(
                    this->shared_from_this(), current_cost() + 1, tmp_conf));
                tmp_conf[blank_x * SIZE + blank_y] = m_conf[blank_x * SIZE + blank_y];
                tmp_conf[blank_x * SIZE + blank_y - 1] = m_conf[blank_x * SIZE + blank_y - 1];
            }

            if (blank_y + 1 < (int) SIZE) {
                tmp_conf[blank_x * SIZE + blank_y] = m_conf[blank_x * SIZE + blank_y + 1];
                tmp_conf[blank_x * SIZE + blank_y + 1] = BLANK;
                succ.emplace_back(std::make_shared<dstate>(
                    this->shared_from_this(), current_cost() + 1, tmp_conf));
            }
            return succ;
        }

        [[nodiscard]] bool is_goal() const override {
            for (size_t i = 0; i < SIZE; i++) {
                for (size_t k = 0; k < SIZE; k++) {
                    if (i == SIZE - 1 && k == SIZE - 1) return true;
                    if (m_conf[i * SIZE + k] != i * SIZE + k)
                        return false;
                }
            }
            return false;
        }

        [[nodiscard]] uint64_t get_identifier() const override {
            return m_id;
        }

        [[nodiscard]] std::string to_string() const override {
            std::ostringstream out;
            out << "[ ";
            for (size_t i = 0; i < SIZE; i++) {
                for (size_t j = 0; j < SIZE; j++) {
                    out << m_conf[i * SIZE + j] << " ";
                }
                if (i != SIZE - 1) out << "| ";
                else out << "]";
            }
            return out.str();
        }

        [[nodiscard]] std::vector<size_t> get_conf() const {
            return m_conf;
        }
    };
};

// explicit instantiation to get type checking
template
class sliding_puzzle<1, 1, 0>;

// verify that we implement the `domain` "interface"
static_assert(domain<sliding_puzzle<1, 1, 0>>);
