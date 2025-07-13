#include "bst_tree.h"

void bst_tree::insert(int64_t data) {
    node* new_node = new node(data);
    node* current = root.load();

    if (current == nullptr) {
        if (root.compare_exchange_strong(current, new_node)) return;
        current = root.load();
    }

    while (true) {
        bool flag = new_node->data < current->data;
        node* next = flag ? current->left.load() : current->right.load();

        if (next == nullptr) {
            if (flag) {
                if (current->left.compare_exchange_strong(next, new_node)) return;
                next = current->left.load();
            } else {
                if (current->right.compare_exchange_strong(next, new_node)) return;
                next = current->right.load();
            }
        }

        current = next;
    }
}

// Rekurzivni funkce pro pruchod stromu a dealokaci pameti prirazene jednotlivym uzlum
void delete_node(bst_tree::node* node) {
    if (node == nullptr) {
        return;
    }

    delete_node(node->left);
    delete_node(node->right);
    delete node;
}

bst_tree::~bst_tree() {
    delete_node(root);
}
