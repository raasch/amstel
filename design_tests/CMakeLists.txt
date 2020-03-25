cmake_minimum_required(VERSION 2.8)

project(AMSTeL_design_tests)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

include_directories("${PROJECT_SOURCE_DIR}/..")

add_executable(test_map_iterators ${PROJECT_SOURCE_DIR}/test_map_iterators.cpp)
add_executable(test_custom_iterators ${PROJECT_SOURCE_DIR}/test_custom_iterators.cpp)
add_executable(test_map_NxN ${PROJECT_SOURCE_DIR}/test_map_NxN.cpp)
add_executable(test_map_NxNxN ${PROJECT_SOURCE_DIR}/test_map_NxNxN.cpp)
