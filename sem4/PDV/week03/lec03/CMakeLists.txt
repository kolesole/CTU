cmake_minimum_required(VERSION 3.15)
project(lectures/03openmp)

set(CMAKE_CXX_STANDARD 20)

# target the instruction set of the current CPU
add_compile_options("-march=native")
# enable LTO
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
# enable more warnings
add_compile_options("-Wall" "-Wextra" "-Wpedantic" "-Wno-unused-parameter")

find_package(OpenMP REQUIRED)
link_libraries(OpenMP::OpenMP_CXX)


add_executable(1hello_world src/1hello_world.cpp)
add_executable(2parallel src/2parallel.cpp)
add_executable(2parallel_omph src/2parallel_omph.cpp)
add_executable(3sections src/3sections.cpp)

add_executable(4for src/4for.cpp)
add_executable(5for_benchmark src/5for_benchmark.cpp)
add_executable(6for_gantt src/6for_gantt.cpp)
add_executable(7for_collapse src/7for_collapse.cpp)

add_executable(8sync src/8sync.cpp)
add_executable(9tasks src/9tasks.cpp)
add_executable(9cancellation src/9cancellation.cpp)
