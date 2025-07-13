#pragma once

#include <array>
#include <sstream>
#include <cmath>
#include <random>
#include <algorithm>
#include <utility>
#include "../state.h"

// NOTE: this code is very non-idiomatic from a performance perspective; however, making the domain faster
//  would make it much harder for you to get a reasonable speedup over the serial solution

/// Domain of the SAT formula satisfiability problem, each state corresponds to a possible variable assignment,
/// each action corresponds to picking a single variable value.
template<size_t NUM_VARS, size_t NUM_CLAUSES, size_t MAX_CLAUSE_SIZE, std::mt19937::result_type SEED, bool UNIFORM>
class sat {
public:
    enum class var_value : uint8_t { FALSE = 0, TRUE = 1, UNDEFINED = 2 };
    using costs_array = std::array<uint64_t, NUM_VARS>;

private:
    std::vector<std::vector<size_t>> m_formula{};
    costs_array m_costs{};

public:
    sat() {
        std::iota(m_costs.begin(), m_costs.end(), 0);
        std::shuffle(m_costs.begin(), m_costs.end(), std::mt19937(SEED)); // NOLINT(*-msc51-cpp)

        std::mt19937 rng(SEED); // NOLINT(*-msc51-cpp)
        std::uniform_int_distribution<int> uni(0, 2 * NUM_VARS - 1);

        std::vector<bool> solution(NUM_VARS);
        for (size_t i = 0; i < NUM_VARS; i++) {
            solution.push_back(uni(rng) % 2);
        }

        m_formula = std::vector<std::vector<size_t>>(NUM_CLAUSES);
        for (size_t i = 0; i < NUM_CLAUSES; i++) {
            size_t size = (uni(rng) % MAX_CLAUSE_SIZE) + 1;
            for (size_t j = 0; j < size; j++) {
                m_formula[i].push_back(uni(rng));
            }
            size_t satisfyingIdx = uni(rng) % NUM_VARS;
            m_formula[i].push_back(satisfyingIdx + solution[satisfyingIdx] * NUM_VARS);
        }
    }

    [[nodiscard]] state_ptr get_root() const {
        return std::make_shared<dstate>(&m_formula, &m_costs);
    }

    friend std::ostream& operator<<(std::ostream& s, const sat& d) {
        s << "Domain: SAT\n";
        s << "Variable count = " << NUM_VARS << ", clause count = " << NUM_CLAUSES
          << ", max clause size = " << MAX_CLAUSE_SIZE + 1 << ", uniform costs = " << (UNIFORM ? "yes" : "no")
          << ", seed = " << SEED << "\n";
        s << "Formula = ";

        auto first = true;
        for (auto& clause : d.m_formula) {
            if (first) first = false;
            else s << " & ";

            s << "( ";
            for (auto var_i : clause) {
                if (var_i >= NUM_VARS) s << "~";
                s << var_i % NUM_VARS << " ";
            }
            s << ")";
        }
        s << "\n";
        return s;
    }

private:
    class dstate final : public state, public std::enable_shared_from_this<dstate> {
    private:
        std::vector<var_value> m_conf;
        uint64_t m_id;

        const std::vector<std::vector<size_t>>* m_formula;
        const costs_array* m_costs;

    public:
        dstate(state_ptr predecessor, uint64_t cost, const std::vector<var_value>& conf,
               const std::vector<std::vector<size_t>>* formula, const costs_array* costs)
            : state(std::move(predecessor), cost), m_conf(conf), m_formula(formula), m_costs(costs) {
            m_id = calculate_id(m_conf);
        }

        dstate(const std::vector<std::vector<size_t>>* formula, const costs_array* costs)
            : state(state_ptr(), 0), m_formula(formula), m_costs(costs) {
            m_conf.resize(NUM_VARS);
            for (size_t i = 0; i < NUM_VARS; i++) {
                m_conf[i] = var_value::UNDEFINED;
            }
            m_id = calculate_id(m_conf);
        }

        [[nodiscard]] std::vector<state_ptr> next_states() const override {
            auto tmp_conf = m_conf;
            std::vector<state_ptr> succ;

            int last_defined_var = -1;
            for (int i = NUM_VARS - 1; i >= 0; i--) {
                if (m_conf[i] != var_value::UNDEFINED) {
                    last_defined_var = i;
                    break;
                }
            }

            for (size_t i = last_defined_var + 1; i < NUM_VARS; i++) {
                uint64_t cost = UNIFORM ? 1 : 1 + (*m_costs)[i];

                tmp_conf[i] = var_value::FALSE;

                if (satisfiable(tmp_conf)) {
                    succ.emplace_back(std::make_shared<dstate>(
                        this->shared_from_this(), current_cost() + cost, tmp_conf, m_formula, m_costs));
                }

                tmp_conf[i] = var_value::TRUE;

                if (satisfiable(tmp_conf)) {
                    succ.emplace_back(std::make_shared<dstate>(
                        this->shared_from_this(), current_cost() + cost, tmp_conf, m_formula, m_costs));
                }

                tmp_conf[i] = var_value::UNDEFINED;
            }
            return succ;
        }

        [[nodiscard]] bool is_goal() const override {
            for (const auto& clause : *m_formula) {
                bool satisfied = false;
                for (auto var : clause) {
                    auto value = var >= NUM_VARS ? var_value::FALSE : var_value::TRUE;
                    int varIdx = var % NUM_VARS;
                    if (m_conf[varIdx] == value) {
                        satisfied = true;
                        break;
                    }
                }
                if (!satisfied) return false;
            }

            return true;
        }

        [[nodiscard]] uint64_t get_identifier() const override {
            return m_id;
        }

        [[nodiscard]] std::string to_string() const override {
            std::ostringstream out;
            for (size_t i = 0; i < NUM_VARS; i++) {
                out << assignment_to_str(m_conf[i]);
            }
            return out.str();
        }

    private:
        static const char* assignment_to_str(var_value value) {
            switch (value) {
                case var_value::FALSE:
                    return "F";
                case var_value::TRUE:
                    return "T";
                case var_value::UNDEFINED:
                    return "-";
                default:
                    return " ";
            }
        }

        static uint64_t calculate_id(const std::vector<var_value>& conf) {
            auto id = (uint64_t) 0ull;
            uint64_t id2 = 0ull; // The whole crazy stuff with id2 is done just to make it slower...
            uint64_t mult = 1ull;
            for (size_t var = 0; var < NUM_VARS; ++var) {
                id += mult * (uint64_t) conf[var];
                id2 += std::pow(3.0, (double) var) * (uint64_t) conf[var];
                mult *= 3;
            }
            auto vmin = std::min<uint64_t>(id, id2);
            return std::max<uint64_t>(vmin, id);
        }

        [[nodiscard]] bool satisfiable(const std::vector<var_value>& state) const {
            // check if it is not refuted by setting
            for (const auto& clause : *m_formula) {
                bool refuted = true;
                for (auto var : clause) {
                    auto value = var >= NUM_VARS ? var_value::FALSE : var_value::TRUE;
                    int varIdx = var % NUM_VARS;
                    if (state[varIdx] == var_value::UNDEFINED || state[varIdx] == value) {
                        refuted = false;
                        break;
                    }
                }
                if (refuted) return false;
            }
            return true;
        }
    };
};

// explicit instantiation to get type checking
template
class sat<1, 1, 1, 0, true>;

// verify that we implement the `domain` "interface"
static_assert(domain<sat<1, 1, 1, 0, true>>);
