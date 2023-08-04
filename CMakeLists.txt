cmake_minimum_required(VERSION 3.10)

project(framework)

set(DEV_DIR ${CMAKE_SOURCE_DIR}/..)

add_subdirectory(${DEV_DIR}/tools/googletest ${CMAKE_BINARY_DIR}/gtest EXCLUDE_FROM_ALL)

add_subdirectory(data)
add_subdirectory(json)