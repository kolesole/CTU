#include <iostream>

class X {
public:
    void do_thing() {
        std::cout << "doing a thing\n";
    }
};

class Y {
public:
    void do_thing() {
        std::cout << "doing another thing\n";
    }
};

class Z {
    // this class cannot do_thing
};

template <typename T>
void fn(T t) {
    t.do_thing();
}

int main() {
    fn(X());
    fn(Y());
    //fn(Z());
}
