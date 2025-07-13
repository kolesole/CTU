#include <iostream>

template <typename T, size_t Size>
class my_array {
    T _array[Size];

public:
    T get(size_t i) {
        return _array[i];
    }

    void set(size_t i, T value) {
        _array[i] = value;
    }
};

int main() {
    auto float_arr = my_array<float, 4>();
    float_arr.set(1, 10.0f);
    std::cout << float_arr.get(1) << "\n";

    auto bool_arr = my_array<bool, 10>();
    bool_arr.set(5, true);
    std::cout << bool_arr.get(5) << "\n";
}
