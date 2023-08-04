add_library(itask INTERFACE)
target_sources(itask INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/itask.cpp)
target_include_directories(itask INTERFACE INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)