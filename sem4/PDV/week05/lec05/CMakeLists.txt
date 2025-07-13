cmake_minimum_required(VERSION 3.15)
project(lectures/05design)

set(CMAKE_CXX_STANDARD 20)

# target the instruction set of the current CPU
add_compile_options("-march=native")
# enable LTO
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
# enable more warnings
add_compile_options("-Wall" "-Wextra" "-Wpedantic" "-Wno-unused-parameter")

find_package(OpenMP REQUIRED)
link_libraries(OpenMP::OpenMP_CXX)


add_executable(1nested_parallel src/1nested_parallel.cpp)
add_executable(2cancellation_for src/2cancellation_for.cpp)
add_executable(3quicksort src/3quicksort.cpp)
add_executable(4prime_sieve src/4prime_sieve.cpp)
