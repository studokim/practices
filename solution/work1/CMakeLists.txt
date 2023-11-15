cmake_minimum_required(VERSION 3.0)

project(work1)

add_executable(work1 main.cpp)

add_library(inih_library
  inih-master/ini.c
  inih-master/cpp/INIReader.cpp
)

target_include_directories(inih_library PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inih-master/cpp)

install(TARGETS inih_library ARCHIVE DESTINATION lib)

target_link_libraries(work1 PRIVATE inih_library)

install(TARGETS work1 RUNTIME DESTINATION bin)
