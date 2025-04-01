cmake_minimum_required(VERSION 3.10)
project(Banking)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Main application
add_executable(my_app bank.cpp main.cpp)

# Google Test setup
set(GTEST_ROOT "/usr/lib/")
find_package(GTest REQUIRED HINTS ${GTEST_ROOT})

include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

# Test suite
add_executable(test_suite bank_tests.cpp bank.cpp)

# Link Google Test properly
target_link_libraries(test_suite PRIVATE ${GTEST_BOTH_LIBRARIES} Threads::Threads)
