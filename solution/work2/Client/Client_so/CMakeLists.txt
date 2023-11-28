cmake_minimum_required(VERSION 3.10)
project(Client VERSION 0.1.0 LANGUAGES C CXX)

# 1. Найти библиотеку ValiDator
find_library(ValiDator_LIB libValiDator.so)

# 2. Создать исполняемый файл
add_executable(Client main.cpp)

# 3. Связать библиотеку с вашим исполняемым файлом
target_link_libraries(Client PRIVATE ${ValiDator_LIB})
