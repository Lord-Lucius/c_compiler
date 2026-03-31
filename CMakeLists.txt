cmake_minimum_required(VERSION 3.10)
project(c_compiler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g")

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/srcs)

file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

add_executable(c_compiler ${SOURCES})

target_include_directories(c_compiler PRIVATE ${INCLUDE_DIR})