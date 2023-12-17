cmake_minimum_required(VERSION 3.0)

project(client)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.42.0 REQUIRED COMPONENTS system thread regex)
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

find_library(validator libvalidator.so PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib)


ADD_EXECUTABLE(client src/main.cpp)
TARGET_LINK_LIBRARIES(client ${USED_LIBS} validator)


