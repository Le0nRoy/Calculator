cmake_minimum_required(VERSION 3.14)
project(Base12Calc)

set(CMAKE_CXX_STANDARD 11)

set(ExecutableName MultyBaseCalculator)
message("Configuring ${ExecutableName}...")

# Include block
include_directories(include)
# Compile block
set(SRC
        src/main.cpp
        src/Expression.cpp
        src/Utils.cpp)
set(HEADERS
        include/Expression.h
        include/Utils.h)

add_executable(${ExecutableName}
        ${SRC}
        ${HEADERS}
        )

# Link block

message("Finished configuring ${ExecutableName}!")
