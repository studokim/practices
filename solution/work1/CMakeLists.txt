cmake_minimum_required(VERSION 3.0)

project(work1)

add_executable(work1 main.cpp)

install(TARGETS work1 RUNTIME DESTINATION bin)
