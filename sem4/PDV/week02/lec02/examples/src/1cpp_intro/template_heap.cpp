#include <iostream>

template <typename T>
class my_array {
    T* _buffer;

public:
    my_array(size_t size) : _buffer(new T[size]) {}

    ~my_array() {
        delete[] _buffer;
    }

    T get(size_t i) {
        return _buffer[i];
    }

    void set(size_t i, T value) {
        _buffer[i] = value;
    }
};

int main() {
    auto float_arr = my_array<float>(4);
    float_arr.set(1, 10.0f);
    std::cout << float_arr.get(1) << "\n";

    auto bool_arr = my_array<bool>(10);
    bool_arr.set(5, true);
    std::cout << bool_arr.get(5) << "\n";
}
