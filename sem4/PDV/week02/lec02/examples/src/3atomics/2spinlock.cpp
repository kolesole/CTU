#include <thread>
#include <iostream>

int main() {
    bool value = false;
    bool value_was_updated = false;

    auto t1 = std::jthread([&] {
        // we set `value` to true
        value = true;
        // then, we set the flag to let the main thread know that we updated the value
        value_was_updated = true;
    });

    // here, we wait until the flag is updated
    while (!value_was_updated) {}
    // now, `value` must obviously be true
    std::cout << "value = " << value << "\n";
}
