add_library(test_listener INTERFACE)
target_include_directories(test_listener INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(test_listener INTERFACE generics)

add_executable(
	generics_tests
	${CMAKE_CURRENT_LIST_DIR}/src/generics_tests.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_dispatcher.cpp
)

target_link_libraries(
	generics_tests
	PRIVATE
	test_listener
	generics
	gtest
	gmock
)