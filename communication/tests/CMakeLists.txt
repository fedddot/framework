add_executable(
	communication_tests
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_package_descriptor.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_package_receiver.cpp
)

target_link_libraries(
	communication_tests
	PRIVATE
	package_descriptor
	package_receiver
	dispatcher
	
	gtest
	gmock
	-g
	-O0
)
