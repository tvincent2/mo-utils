cmake_minimum_required(VERSION 2.8)
project(mo-utils-tests)
include_directories(../include)
find_library(CPPUNIT_LIBRARY cppunit)

set(TESTS_SRC main.cpp
              BVectTest.cpp
              BEdgeTest.cpp)

add_executable(mo_utils_tests ${TESTS_SRC})
target_link_libraries(mo_utils_tests ${CPPUNIT_LIBRARY})
