cmake_minimum_required(VERSION 3.30)
project(demo_vector_exp)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP REQUIRED)

add_executable(main src/main.cpp)
target_link_libraries(main PUBLIC OpenMP::OpenMP_CXX)
