cmake_minimum_required(VERSION 3.15)
project(pdv_lab08)

set(CMAKE_CXX_STANDARD 20)

# target the instruction set of the current CPU
add_compile_options("-march=native")
# enable LTO
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
# enable more warnings
add_compile_options("-Wall" "-Wextra" "-Wpedantic")

# OpenMP 4.0 is required for user defined reductions
find_package(OpenMP 4.0 REQUIRED)

add_executable(08_sparse_multiplication src/main.cpp src/multiply.cpp)
target_link_libraries(08_sparse_multiplication PUBLIC OpenMP::OpenMP_CXX)
