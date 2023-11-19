cmake_minimum_required(VERSION 3.5)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# Set the project name
project (myApp)

set(myMathLibFolder ${CMAKE_CURRENT_SOURCE_DIR}/../myMath)

# # Add an executable
add_executable(myApp main.cpp)
target_include_directories(myApp PUBLIC ${myMathLibFolder}/include/)
target_link_libraries(myApp ${myMathLibFolder}/build/libmyMath.a)

