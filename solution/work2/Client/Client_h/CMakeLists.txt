cmake_minimum_required(VERSION 3.10)
project(Client VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Client main.cpp)

add_library(LibValidator
    ValiDator/src/ValiDator.h
)

target_include_directories(LibValidator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ValiDator/src)

set_target_properties(LibValidator PROPERTIES LINKER_LANGUAGE CXX)

install(
    TARGETS LibValidator
    ARCHIVE DESTINATION lib
)

target_link_libraries(Client PRIVATE LibValidator)

install(
    TARGETS Client
    RUNTIME DESTINATION bin
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
