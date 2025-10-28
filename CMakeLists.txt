cmake_minimum_required(VERSION 3.10.0)
project(CLI VERSION 0.1.0 LANGUAGES C)

add_executable(CLI CLI.c main.c)

include(CTest)
enable_testing()

