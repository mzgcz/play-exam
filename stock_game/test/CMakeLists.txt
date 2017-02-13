cmake_minimum_required(VERSION 2.6)

project(myTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

aux_source_directory(.. CODE_SRC_LIST)
aux_source_directory(. TEST_SRC_LIST)

add_executable(myTest ${CODE_SRC_LIST} ${TEST_SRC_LIST})
target_link_libraries(myTest ${GTEST_MAIN_LIBRARIES} ${GTEST_LIBRARIES} pthread)
