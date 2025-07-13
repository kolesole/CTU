/// A naive implementation of a lock-free stack that leaks nodes to avoid the ABA and lifetime problems.

#include <atomic>
#include <iostream>
#include <optional>
template <typename T>
class lock_free_stack {
    class node;

private:
    std::atomic<node*> m_head;

public:
    void push(T value) {
        auto new_node = new node(value);
        auto first_node = m_head.load();
        do {
            new_node->m_next = first_node;
            // if the condition below fails, `first_node` is updated to the current value
        } while (!m_head.compare_exchange_weak(first_node, new_node));
    }

    [[nodiscard]] bool contains(T value) const {
        auto node = m_head.load();
        while (node != nullptr) {
            if (node->m_value == value) {
                return true;
            }
            node = node->m_next.load();
        }
        return false;
    }

    // NAIVE IMPLEMENTATION, WILL NOT WORK IF YOU DEALLOCATE THE NODE
    std::optional<T> pop() {
        auto first_node = m_head.load();
        while (first_node != nullptr) {
            auto second_node = first_node->m_next.load();
            if (m_head.compare_exchange_weak(first_node, second_node)) {
                // LEAK first_node (do not deallocate)
                return first_node->m_value;
            }
            // retry, first_node is updated to the new value
        }
        return {};
    }

private:
    class node {
    public:
        std::atomic<node*> m_next = nullptr;
        T m_value;

        explicit node(T value) : m_value(value) {}
    };
};

int main() {
    auto stack = lock_free_stack<uint32_t>();
    #pragma omp parallel for
    for (size_t i = 0; i < 100; i++) {
        stack.push(i);
    }

    for (size_t i = 0; i < 100; i++) {
        if (!stack.contains(i)) {
            std::cout << "missing " << i << "\n";
        }
    }

    std::cout << "\n";
    while (true) {
        auto value = stack.pop();
        if (!value) {
            break;
        }
        std::cout << *value << "\n";
    }
}
