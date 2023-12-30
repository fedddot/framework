add_executable(
	communication_tests
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	# ${CMAKE_CURRENT_LIST_DIR}/src/ut_package_descriptor.cpp
	# ${CMAKE_CURRENT_LIST_DIR}/src/ut_package_receiver.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_communication_manager.cpp
)

target_link_libraries(
	communication_tests
	PRIVATE
	# package_descriptor
	# package_receiver
	communication_manager
	test_listener
	
	gtest
	gmock
	-g
	-O0
)
