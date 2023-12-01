cmake_minimum_required(VERSION 3.10)

project(framework)

set(DEV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(GTEST_DIR ${DEV_DIR}/tools/googletest)

add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/gtest EXCLUDE_FROM_ALL)

add_library(ilistener INTERFACE)
target_include_directories(ilistener INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(dispatcher INTERFACE)
target_include_directories(dispatcher INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(icreator INTERFACE)
target_include_directories(icreator INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(factory INTERFACE)
target_include_directories(factory INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(registry INTERFACE)
target_include_directories(registry INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(data)
add_subdirectory(task)
add_subdirectory(json)
add_subdirectory(communication)
add_subdirectory(state_machine)