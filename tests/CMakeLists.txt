message("Configuring ${TEST_EXECUTABLE_NAME}...")

enable_testing()

add_subdirectory(lib)

# Include block
include_directories(
        ${${MAIN_LIB_NAME}_SOURCE_DIR}
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
)

# Compile block
set(TEST_SRC
        main_test.cpp
        BaseOperationsTests.cpp
        ExpressionTests.cpp
        )

add_executable(${TEST_EXECUTABLE_NAME}
        ${TEST_SRC}
        )

add_test(TEST ${TEST_EXECUTABLE_NAME} COMMAND ${TEST_EXECUTABLE_NAME})

# Link block
set(LINK_LIBS
        ${MAIN_LIB_NAME}_lib
        gtest
        )

target_link_libraries(${TEST_EXECUTABLE_NAME}
        ${LINK_LIBS}
        )

message("Finished configuring ${TEST_EXECUTABLE_NAME}!")
