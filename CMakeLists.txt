cmake_minimum_required(VERSION 3.28)
project(ProjetoDA2)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProjetoDA2 src/main.cpp
        src/Menu.h
        src/System.h
        src/Menu.cpp
        src/System.cpp
        src/Graph.h
        src/Node.h
        src/Edge.h
        src/Graph.cpp
        src/Node.cpp
        src/Edge.cpp)
