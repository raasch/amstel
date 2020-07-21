cmake_minimum_required(VERSION 2.8)

project(AMSTeL_unit_tests)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
# set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}/..")

add_executable(test_infinite_vector ${PROJECT_SOURCE_DIR}/test_infinite_vector.cpp)
add_executable(test_array1d ${PROJECT_SOURCE_DIR}/test_array1d.cpp)