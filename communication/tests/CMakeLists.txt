add_executable(
	communication_tests
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_package_descriptor.cpp
)

target_link_libraries(
	communication_tests
	PRIVATE
	package_descriptor
	
	gtest
	gmock
	-g
	-O0
)
