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

# Установка целей
set(LIB_DIR lib)
install(
    TARGETS ValiDator
    LIBRARY DESTINATION ${LIB_DIR}
    PUBLIC_HEADER DESTINATION ${INCLUDE_DIR}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Добавление исполняемых файлов для каждого теста
add_executable(TestCreditCardNumberValidator tests/TestCreditCardNumberValidator.cpp)
add_executable(TestPassportValidator tests/TestPassportValidator.cpp)
add_executable(TestPhoneNumberValidator tests/TestPhoneNumberValidator.cpp)

# Подключение к цели
target_link_libraries(TestCreditCardNumberValidator PRIVATE ValiDator)
target_link_libraries(TestPassportValidator PRIVATE ValiDator)
target_link_libraries(TestPhoneNumberValidator PRIVATE ValiDator)

# Добавление тестов с использованием ctest
add_test(NAME TestCreditCardNumberValidator COMMAND TestCreditCardNumberValidator)
add_test(NAME TestPassportValidator COMMAND TestPassportValidator)
add_test(NAME TestPhoneNumberValidator COMMAND TestPhoneNumberValidator)