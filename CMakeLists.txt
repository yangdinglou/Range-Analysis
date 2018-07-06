cmake_minimum_required(VERSION 3.10)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project main.cpp Func.cpp Func.h section.h Parser.h scc.cpp scc.h tarjan.h)