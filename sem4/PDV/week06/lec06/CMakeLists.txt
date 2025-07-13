cmake_minimum_required(VERSION 3.15)
project(lectures/06sort)

set(CMAKE_CXX_STANDARD 20)

if(NOT ${MSVC})
    # target the instruction set of the current CPU
    add_compile_options("-march=native")
    # enable more warnings
    add_compile_options("-Wall" "-Wextra" "-Wpedantic" "-Wno-unused-parameter")
endif()

# enable LTO
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

find_package(OpenMP REQUIRED)
link_libraries(OpenMP::OpenMP_CXX)


file(GLOB files "src/*.cpp")
foreach(file_path ${files})
    get_filename_component(file_name ${file_path} NAME_WE)
    add_executable(${file_name} ${file_path})
endforeach ()
