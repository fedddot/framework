cmake_minimum_required(VERSION 3.10)

project(framework)

set(DEV_DIR ${CMAKE_SOURCE_DIR}/..)
set(GTEST_DIR ${DEV_DIR}/tools/googletest)

add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/gtest EXCLUDE_FROM_ALL)

add_library(ilistener INTERFACE)
target_include_directories(ilistener INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(itask INTERFACE)
target_sources(itask INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/itask.cpp)
target_include_directories(itask INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(data)
add_subdirectory(json)
add_subdirectory(communication)