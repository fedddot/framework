add_executable(
	json_tests_exec
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_json_parser.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/ut_json_serializer.cpp
)

target_link_libraries(
	json_tests_exec
	PRIVATE
	
	idata
	array
	object
	string
	
	json_common

	idata_parser
	json_parser

	idata_serializer
	json_serializer	
	
	gtest
	gmock
)
