cmake_minimum_required(VERSION 3.5)
#powyższa pewnie jednak nie wystarcza
project(Shell)
set(CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "builds")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "debug")


file(GLOB SOURCES "*.cpp")
add_executable(Shell ${SOURCES})
add_executable(first-tested programs/first-tested.cpp)
add_executable(tested programs/tested.cpp)

