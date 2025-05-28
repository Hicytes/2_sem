cmake_minimum_required(VERSION 3.10)
project(BisectionMethod C)

set(CMAKE_C_STANDARD 99)

add_executable(bisection
    main.c
    bisection.c
    functions.c
)

target_link_libraries(bisection m)

add_custom_command(
    OUTPUT data.txt
    COMMAND bisection > data.txt
    DEPENDS bisection
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running bisection to generate data.txt"
)

add_custom_target(run_data ALL DEPENDS data.txt)
