cmake_minimum_required(VERSION 3.10)
project(ValiDator VERSION 1.0)

include(CTest)
enable_testing()

# Указание исходных файлов
set(SOURCE_FILES src/ValiDator.cpp)

# Создание shared библиотеки
add_library(ValiDator SHARED ${SOURCE_FILES})


# Создание архива .tar.gz
set(ARCHIVE_NAME "ValiDator")
set(LIB_DIR lib)
set(BUILD_DIR build)
set(SRC_DIR src)
set(TAR_DIR ${ARCHIVE_NAME})

add_custom_command(TARGET ValiDator
    POST_BUILD
    COMMAND mkdir -p ${TAR_DIR}/${LIB_DIR}
    COMMAND cp $<TARGET_FILE:ValiDator> ${TAR_DIR}/${LIB_DIR}/
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}/ValiDator.h ${TAR_DIR}/
    COMMAND tar -czf ${ARCHIVE_NAME}-${PROJECT_VERSION}.tar.gz ${TAR_DIR}
    COMMAND rm -rf ${TAR_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Creating archive"
    VERBATIM
)

# Добавляем цель для выполнения скрипта
add_custom_target(header_only_script
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/head_only.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating header-only version"
    VERBATIM
)

add_dependencies(ValiDator header_only_script)

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
