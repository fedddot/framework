cmake_minimum_required(VERSION 3.10)

project(framework)

set(DEV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(GTEST_DIR ${DEV_DIR}/tools/googletest)

add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/gtest EXCLUDE_FROM_ALL)

add_subdirectory(data)
add_subdirectory(task)
add_subdirectory(json)
add_subdirectory(generics)
add_subdirectory(communication)
add_subdirectory(state_machine)