set(myMathDir ${CMAKE_CURRENT_SOURCE_DIR}/../myMath)

set(HEADER_FILES ${myMathDir}/include/myMath.hpp)
add_library(myMath ${myMathDir}/myMath.cpp ${HEADER_FILES})
target_include_directories(myMath PRIVATE ${myMathDir})