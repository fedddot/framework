add_library(itask INTERFACE)
target_sources(itask INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/itask.cpp)
target_include_directories(itask INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(movement_task INTERFACE)
target_sources(movement_task INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/movement_task.cpp)
target_include_directories(movement_task INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(movement_task INTERFACE itask)

add_library(movement_task_test STATIC)
target_link_libraries(movement_task_test PRIVATE movement_task)