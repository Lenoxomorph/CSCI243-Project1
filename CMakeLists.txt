cmake_minimum_required(VERSION 3.23)
project(project1 C)

set(CMAKE_C_STANDARD 99)

add_executable(project1 tokenize.c tokenize.h
        scanner.c
        scanner.h
)
