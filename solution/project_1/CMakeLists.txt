cmake_minimum_required(VERSION 3.0)

project(project_1)


add_executable(project_1 main.cpp)

add_library(inih_lib
 inih/ini.c
 inih/cpp/INIReader.cpp)

target_include_directories(inih_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inih/cpp)

install(TARGETS inih_lib ARCHIVE DESTINATION lib)

target_link_libraries(project_1 PRIVATE inih_lib)

install(TARGETS project_1 RUNTIME DESTINATION bin)
