cmake_minimum_required(VERSION 3.13)
project(RGRIDE)

set(CMAKE_CXX_STANDARD 17)

add_executable(RGRIDE main.cpp Vertex.h Graph.h Edge.h Form.h)