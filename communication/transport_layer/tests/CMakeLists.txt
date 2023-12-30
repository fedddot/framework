add_executable(
	transport_layer_tests
	${CMAKE_CURRENT_LIST_DIR}/src/transport_layer_tests.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_uart_communication_manager.cpp
)

target_link_libraries(
	transport_layer_tests
	PRIVATE
	uart_communication_manager
	
	gtest
	gmock
	-g
	-O0
)
