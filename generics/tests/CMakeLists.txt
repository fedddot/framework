add_executable(
	generics_tests
	${CMAKE_CURRENT_LIST_DIR}/src/generics_tests.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_dispatcher.cpp
)

target_link_libraries(
	generics_tests
	PRIVATE
	generics
	gtest
	gmock
)