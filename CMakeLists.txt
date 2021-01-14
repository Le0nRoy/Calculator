cmake_minimum_required(VERSION 3.14)
project(Base12Calc)

set(CMAKE_CXX_STANDARD 11)

set(ExecutableName MultyBaseCalculator)
# Name of lib for tests should be same as project name in order to get src dir
set(MAIN_LIB_NAME ${PROJECT_NAME})
message("Configuring ${ExecutableName}...")

# Include block
include_directories(include)
# Compile block
set( SRC
     src/Utils.cpp
     src/Expression.cpp
     src/BinaryOperation.cpp
     src/Number.cpp
     )
set( HEADERS
     include/Utils.h
     include/Expression.h
     include/BinaryOperation.h
     include/Number.h )

add_library(${MAIN_LIB_NAME}
        ${SRC}
        ${HEADERS}
        )

#add_executable(${ExecutableName}
#        src/main.cpp
#        ${SRC}
#        ${HEADERS}
#        )

# Link block

# Test block
add_subdirectory(tests)

message("Finished configuring ${ExecutableName}!")
