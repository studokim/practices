cmake_minimum_required(VERSION 3.10)
project(validator VERSION 1.0)


# Указание исходных файлов
set(SOURCE_FILES src/validator.cpp)

# Создание shared библиотеки
add_library(validator SHARED ${SOURCE_FILES})

# Установка заголовочных файлов
set(INCLUDE_DIR include)
set_target_properties(validator PROPERTIES PUBLIC_HEADER src/validator.h)
target_include_directories(validator PRIVATE ${INCLUDE_DIR})

# Установка целей
set(LIB_DIR lib)
install(
    TARGETS validator
    LIBRARY DESTINATION ${LIB_DIR}
    PUBLIC_HEADER DESTINATION ${INCLUDE_DIR}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)