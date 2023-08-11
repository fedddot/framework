add_library(isender INTERFACE)
target_include_directories(isender INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(ireceiver INTERFACE)
target_include_directories(ireceiver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(ireceiver INTERFACE ilistener)

add_library(icommunication_manager INTERFACE)
target_include_directories(icommunication_manager INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(icommunication_manager INTERFACE isender ireceiver)