add_library(state_machine INTERFACE)
target_include_directories(state_machine INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(tests EXCLUDE_FROM_ALL)