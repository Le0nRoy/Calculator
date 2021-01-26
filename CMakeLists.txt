cmake_minimum_required(VERSION 3.14)
project(Calculator)

set(CMAKE_CXX_STANDARD 11)

set(MAIN_LIB_NAME ${PROJECT_NAME})
set(TEST_EXECUTABLE_NAME ${PROJECT_NAME}_tests)

include_directories(include)

message("Configuring ${MAIN_LIB_NAME}...")

# Compile block
set( SRC
        src/Expression.cpp
        src/BinaryOperation.cpp
        src/Number.cpp
        src/NumberSystemConverter.cpp
        )
add_library(${MAIN_LIB_NAME}_lib
        ${SRC}
        )

# Tests block
add_subdirectory(tests)

# TODO make tests being launched
# Executable compilation block
add_executable(${MAIN_LIB_NAME}
        src/frontend/main.cpp
        ${SRC}
        )

message("Finished configuring ${MAIN_LIB_NAME}!")
