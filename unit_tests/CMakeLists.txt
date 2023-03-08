cmake_minimum_required(VERSION 3.12)

project(AMSTeL_unit_tests)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
# set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}/..")

add_executable(test_array1d ${PROJECT_SOURCE_DIR}/test_array1d.cpp)
target_compile_features(test_array1d PUBLIC cxx_std_20)

add_executable(test_array2d ${PROJECT_SOURCE_DIR}/test_array2d.cpp)
target_compile_features(test_array2d PUBLIC cxx_std_20)

add_executable(test_infinite_vector ${PROJECT_SOURCE_DIR}/test_infinite_vector.cpp)
target_compile_features(test_infinite_vector PUBLIC cxx_std_20)

add_executable(test_grid ${PROJECT_SOURCE_DIR}/test_grid.cpp)
target_compile_features(test_grid PUBLIC cxx_std_20)
