add_executable(
	state_machine_tests
	${CMAKE_CURRENT_LIST_DIR}/src/state_machine_tests.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_state_machine.cpp
)

target_link_libraries(
	state_machine_tests
	PRIVATE
	state_machine	
	gtest
	gmock
)
