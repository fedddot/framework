add_library(uart_types INTERFACE)
target_include_directories(uart_types INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(uart INTERFACE)
target_sources(uart INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/uart.cpp)
target_include_directories(uart INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(uart INTERFACE uart_types ibytes_reader ibytes_writer)