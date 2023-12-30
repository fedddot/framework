add_library(generics INTERFACE)
target_include_directories(generics INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(tests EXCLUDE_FROM_ALL)