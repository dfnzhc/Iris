cmake_minimum_required(VERSION 3.27)

project(${PROJECT_NAME}Test LANGUAGES CXX)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

find_package(GTest CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)

# These examples use the standard separate compilation
set(TEST_SOURCES
        Base/LogTest.cpp
        BaseTest.cpp
        CommonTest.cpp
)

set(${CMAKE_CURRENT_BINARY_DIR})

foreach (FILE ${TEST_SOURCES})
    get_filename_component(FILE_NAME ${FILE} NAME_WE)
    add_executable(${FILE_NAME} ${FILE})
    set_property(TARGET ${FILE_NAME} PROPERTY FOLDER "Tests")

    target_link_libraries(${FILE_NAME} 
            PUBLIC GTest::gtest GTest::gtest_main benchmark::benchmark 
            PRIVATE Iris)
    set_target_properties(${FILE_NAME} PROPERTIES
            CXX_STANDARD 23
            RUNTIME_OUTPUT_DIRECTORY ${IRIS_RUNTIME_OUTPUT_DIR}
            LIBRARY_OUTPUT_DIRECTORY ${IRIS_LIBRARY_OUTPUT_DIR}
    )

    add_test(NAME "${FILE_NAME}Test" 
            COMMAND ${FILE_NAME}
            WORKING_DIRECTORY ${IRIS_RUNTIME_OUTPUT_DIR})
endforeach ()
