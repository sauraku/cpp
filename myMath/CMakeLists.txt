cmake_minimum_required(VERSION 3.5)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# Set the project name
project (myMath)

# add libraries
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/myMath.hpp)
add_library(myMath myMath.cpp ${HEADER_FILES})
target_include_directories(myMath PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})



# # Add an executable
# add_executable(myexec main.cpp ${HEADER_FILES})
# target_include_directories(myexec PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})