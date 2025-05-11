cmake_minimum_required(VERSION 3.10)
project(BisectionMethod C)

set(CMAKE_C_STANDARD 99)

add_executable(bisection
    main.c
    bisection.c
    functions.c
)

target_link_libraries(bisection m)

