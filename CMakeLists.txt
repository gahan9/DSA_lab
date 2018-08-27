cmake_minimum_required(VERSION 3.12)
project(DSA_lab C)

set(CMAKE_C_STANDARD 99)

add_executable(DSA_lab sort/program.c sort/constant.h sort/utility.h sort/sorting_algorithms.h 4_aray_b_plus_tree.c refs/b_tree.c)