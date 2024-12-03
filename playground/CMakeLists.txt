cmake_minimum_required(VERSION 3.27)
project(util_playground)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES playground.cpp ../util.cpp)

add_executable(util_playground ${SOURCES})
