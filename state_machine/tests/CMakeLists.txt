add_executable(
	state_machine_tests_exec
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_state_machine.cpp
)

target_link_libraries(
	state_machine_tests_exec
	PRIVATE
	state_machine	
	gtest
	gmock
)
