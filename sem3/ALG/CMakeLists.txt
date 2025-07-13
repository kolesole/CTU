cmake_minimum_required(VERSION 3.29)
project(ALG C)

set(CMAKE_C_STANDARD 11)

# hw01
add_executable(hw01_main
        hw01/dfs.c
        hw01/dfs.h
        hw01/main.c
        hw01/rectangle.c
        hw01/rectangle.h
        hw01/utils.c
        hw01/utils.h
        hw01/zero.c
        hw01/zero.h
)

target_include_directories(hw01_main PRIVATE hw01)

# hw02
add_executable(hw02_main
        hw02/main.c
        hw02/utils.h
        hw02/utils.c
        hw02/aux_grid.c
        hw02/aux_grid.h
        hw02/sensor.c
        hw02/sensor.h
        hw02/placement.h
        hw02/placement.c
        hw02/position.h
        hw02/position.c
        hw02/backtracking.h
        hw02/backtracking.c
)

target_include_directories(hw02_main PRIVATE hw02)

# hw03
add_executable(hw03_main
        hw03/main.c
        hw03/read.c
        hw03/read.h
        hw03/tree.h
        hw03/tree.c
        hw03/dfs.c
        hw03/dfs.h
)

target_include_directories(hw03_main PRIVATE hw03)

add_executable(hw04_main
        hw04/main.c
        hw04/utils.h
        hw04/utils.c
        hw04/aux_matrix.h
        hw04/aux_matrix.c
        hw04/queue.h
        hw04/queue.c
        hw04/bfs.h
        hw04/bfs.c
)

target_include_directories(hw04_main PRIVATE hw04)

add_executable(hw05_main
        hw05/main.c
        hw05/utils.h
        hw05/utils.c
        hw05/bvs_tree.h
        hw05/bvs_tree.c
)

target_include_directories(hw05_main PRIVATE hw05)

# hw06
add_executable(hw06_main
        hw06/main.c
        hw06/utils.h
        hw06/utils.c
        hw06/oavl_tree.h
        hw06/oavl_tree.c
        hw06/rotation.h
        hw06/rotation.c
        hw06/oavl_utils.h
        hw06/oavl_utils.c
)

target_include_directories(hw06_main PRIVATE hw06)

# hw07
add_executable(hw07_main
        hw07/main.c
        hw07/utils.h
        hw07/utils.c
        hw07/post.h
        hw07/post.c
        hw07/queue.h
        hw07/queue.c
        hw07/sorting.h
        hw07/sorting.c
)

target_include_directories(hw07_main PRIVATE hw07)

# hw08
add_executable(hw08_main
        hw08/main.c
        hw08/utils.h
        hw08/utils.c
        hw08/attractiveness.c
        hw08/attractiveness.h
        hw08/converter.h
        hw08/converter.c
)

target_include_directories(hw08_main PRIVATE hw08)
