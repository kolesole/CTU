cmake_minimum_required(VERSION 3.15)
project(lectures/04cds)

set(CMAKE_CXX_STANDARD 20)

# target the instruction set of the current CPU
add_compile_options("-march=native")
# enable LTO
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
# enable more warnings
add_compile_options("-Wall" "-Wextra" "-Wpedantic" "-Wno-unused-parameter")

find_package(OpenMP REQUIRED)
link_libraries(OpenMP::OpenMP_CXX)


file(GLOB files "src/*.cpp")
foreach(file_path ${files})
    get_filename_component(file_name ${file_path} NAME_WE)
    add_executable(${file_name} ${file_path})
endforeach ()
