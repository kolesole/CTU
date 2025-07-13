#include "../pdv_lib/pdv_lib.hpp"

void critical() {
    auto vec = pdv::generate_random_vector<float>(1'000'000, 0);
    auto full_sum = 0.0;

    #pragma omp parallel
    {
        auto sum = 0.0;

        #pragma omp for
        for (auto f : vec) {
            sum += f;
        }

        // critical section (internally, this section is protected with a mutex)
        #pragma omp critical
        {
            full_sum += sum;
        }
    }

    std::cout << "sum = " << full_sum << "\n";
}





void single() {
    #pragma omp parallel
    {
        std::cout << "multiple threads\n";

        #pragma omp single
        std::cout << "single thread\n";

        std::cout << "again multiple threads\n";
    }
}

void barrier() {
    #pragma omp parallel
    {
        std::cout << "multiple threads\n";

        // all threads wait here for each other
        #pragma omp barrier

        #pragma omp single
        std::cout << "single thread\n";

        #pragma omp barrier

        std::cout << "again multiple threads\n";
    }

    std::cout << "after parallel\n";
}



void reduction() {
    auto vec = pdv::generate_random_vector<float>(1'000'000, 0);
    auto sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (auto f : vec) {
        sum += f;
    }

    std::cout << "sum = " << sum << "\n";
}




struct X {};
void reduceX(X& x1, X& x2) {
    //...
}

// we won't be using custom reductions in PDV
void reduction_custom() {
    #pragma omp declare reduction( \
	    reduceX : X : reduceX(omp_out, omp_in) \
    ) initializer (omp_priv=omp_orig)

    X x;
    #pragma omp parallel reduction(reduceX:x)
    {
        // ...
    }
}

int main() {
    critical();
//    single();
//    barrier();
//    reduction();
}
