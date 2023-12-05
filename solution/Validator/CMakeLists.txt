cmake_minimum_required(VERSION 3.10)
project(Validator VERSION 1.0)

set(SOURCE_FILES dynamic_link/Validator.cpp)

add_library(Validator SHARED ${SOURCE_FILES})

set(INCLUDE_DIR include)
set_target_properties(Validator PROPERTIES PUBLIC_HEADER dynamic_link/Validator.h)
target_include_directories(Validator PRIVATE ${INCLUDE_DIR})

install(TARGETS Validator
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include)