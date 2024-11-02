cmake_minimum_required(VERSION 3.15)
project(sovarian)

set(CXX_STANDARD            23)
set(CXX_STANDARD_REQUIRED TRUE)

set(EXECUTABLE ${PROJECT_NAME})
add_executable(${EXECUTABLE} main.cpp)