#include <iostream>
int main() {
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                std::cout << "hello\n";
            }

            #pragma omp section
            {
                std::cout << "parallel\n";
            }

            #pragma omp section
            {
                std::cout << "world\n";
            }
        }

        std::cout << "after sections\n";
    }
}
