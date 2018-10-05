cmake_minimum_required(VERSION 3.12)
project(DSA_lab C)

set(CMAKE_C_STANDARD 99)

add_executable(utils/constant.h utils/utility.h)
add_executable(sort/program.c sort/sorting_algorithms.h)
add_executable(greedy/recursive_exponential.c greedy/krushkal_disjoint_ds.c)
add_executable(bPlusTree/bPlusTree.c)