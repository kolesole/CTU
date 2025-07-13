#include <iostream>
#include <syncstream>

int main() {
    #pragma omp parallel
    {
        std::osyncstream(std::cout) << "Hello " << "world!" << "\n";
    }
}
