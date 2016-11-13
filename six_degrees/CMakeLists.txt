cmake_minimum_required(VERSION 3.5)
project(SixDegreesOfSeparation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp GraphActors.cpp GraphActors.h LinkedList.cpp LinkedList.h)
add_executable(SixDegreesOfSeparation ${SOURCE_FILES})