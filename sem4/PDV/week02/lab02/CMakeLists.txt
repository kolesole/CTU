cmake_minimum_required(VERSION 3.15)
project(pdv_lab02)

set(CMAKE_CXX_STANDARD 20)

# target the instruction set of the current CPU
add_compile_options("-march=native")
# enable LTO
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
# enable more warnings
add_compile_options("-Wall" "-Wextra" "-Wpedantic" "-Wno-unused-parameter")


find_package(Threads REQUIRED)
find_package(OpenMP REQUIRED)


add_executable(02_1threads src/1threads_benchmark.cpp src/1threads.cpp)
add_executable(02_2condition_variable src/2condition_variable.cpp)

target_link_libraries(02_1threads PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(02_2condition_variable PUBLIC Threads::Threads)

# commented out, otherwise students would have to install TBB
# # ensure we support C++17 parallel algorithms
# # GCC & Clang needs to be linked with Intel TBB, which is used to implement parallel algorithms
# find_package(TBB REQUIRED tbb)
# target_link_libraries(02_1threads PUBLIC TBB::tbb)
# if(Clang)
#    # Clang additionally needs to use stdlibc++ on non-Windows OSs instead of libc++,
#    #  because libc++ does not support parallel algorithms at all
#    target_link_libraries(02_1threads PUBLIC "-stdlib=stdlibc++")
# endif()
