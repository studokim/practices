cmake_minimum_required(VERSION 3.12)
project(ValidatorModule LANGUAGES CXX)

find_package(pybind11 REQUIRED)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

pybind11_add_module(libvalidator bindings.cpp)

# Линковка с библиотекой
target_link_libraries(libvalidator PRIVATE Validator)
