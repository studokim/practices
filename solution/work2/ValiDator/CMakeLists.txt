cmake_minimum_required(VERSION 3.10)
project(ValiDator VERSION 1.0)

include(CTest)
enable_testing()

# Указание исходных файлов
set(SOURCE_FILES src/ValiDator.cpp)

# Создание shared библиотеки
add_library(ValiDator SHARED ${SOURCE_FILES})

# Установка заголовочных файлов
set(INCLUDE_DIR include)
set_target_properties(ValiDator PROPERTIES PUBLIC_HEADER src/ValiDator.h)
target_include_directories(ValiDator PRIVATE ${INCLUDE_DIR})

# Указание пути для сборки библиотеки
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/so_lib)
set_target_properties(ValiDator PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})


# Добавление тестов только при использовании опции BUILD_TESTING и сборке в режиме Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Добавление исполняемых файлов для каждого теста
    add_executable(TestCreditCardNumberValidator tests/TestCreditCardNumberValidator.cpp)
    add_executable(TestPassportValidator tests/TestPassportValidator.cpp)
    add_executable(TestPhoneNumberValidator tests/TestPhoneNumberValidator.cpp)

    # Подключение к библиотеке или цели, которую вы хотите протестировать
    target_link_libraries(TestCreditCardNumberValidator PRIVATE ValiDator)
    target_link_libraries(TestPassportValidator PRIVATE ValiDator)
    target_link_libraries(TestPhoneNumberValidator PRIVATE ValiDator)

    # Добавление тестов с использованием ctest
    add_test(NAME TestCreditCardNumberValidator COMMAND TestCreditCardNumberValidator)
    add_test(NAME TestPassportValidator COMMAND TestPassportValidator)
    add_test(NAME TestPhoneNumberValidator COMMAND TestPhoneNumberValidator)
endif()
