cmake_minimum_required(VERSION 3.6)
project(ass4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES test01.cpp btree.h btree_iterator.h)
add_executable(ass4 ${SOURCE_FILES})