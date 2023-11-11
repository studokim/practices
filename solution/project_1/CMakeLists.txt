cmake_minimum_required(VERSION 3.0)

project(project_1)


add_executable(project_1 main.cpp)
install(TARGETS project_1 RUNTIME DESTINATION bin)
