cmake_minimum_required(VERSION 3.0)

project(project_1)

add_executable(project_1 main.cpp)

add_library(inih_library
  inih-master/ini.c
  inih-master/cpp/INIReader.cpp
)

target_include_directories(inih_library PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inih-master/cpp)

install(TARGETS inih_library ARCHIVE DESTINATION lib)

target_link_libraries(project_1 PRIVATE inih_library)

install(TARGETS project_1 RUNTIME DESTINATION bin)
