cmake_minimum_required(VERSION 3.30)
project(lectures/02cpp)

set(CMAKE_CXX_STANDARD 20)

# enable more warnings
add_compile_options("-Wall" "-Wextra" "-Wpedantic" "-Wno-unused-parameter")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # target the instruction set of the current CPU
    add_compile_options("-march=native")
    # enable LTO
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

find_package(Threads REQUIRED)
link_libraries(Threads::Threads)

add_executable(1_main src/1cpp_intro/main.cpp)
add_executable(1_template_fn src/1cpp_intro/template_fn.cpp)
add_executable(1_template_array src/1cpp_intro/template_array.cpp)
add_executable(1_template_heap src/1cpp_intro/template_heap.cpp)

add_executable(2_1jthread src/2threads/1jthread.cpp)
add_executable(2_1synchronization src/2threads/2synchronization.cpp)

add_executable(3_1increment src/3atomics/1increment.cpp)
add_executable(3_1increment_atomic src/3atomics/1increment_atomic.cpp)
add_executable(3_2spinlock src/3atomics/2spinlock.cpp)
add_executable(3_2spinlock_atomic src/3atomics/2spinlock_atomic.cpp)
