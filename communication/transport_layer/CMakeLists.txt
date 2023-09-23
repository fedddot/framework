add_library(uart INTERFACE)
target_sources(uart INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/uart.cpp)
target_include_directories(uart INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(uart INTERFACE isender ilistener dispatcher)

add_library(uart_test STATIC)
target_link_libraries(uart_test PRIVATE uart)