cmake_minimum_required(VERSION 3.25)
project(stella C)

set(CMAKE_C_STANDARD 11)

add_executable(stella main.c lex.c lex.h plain.c retval.c name.c args.c)
