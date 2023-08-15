add_library(json_parser INTERFACE)
target_sources(json_parser INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/json_parser.cpp)
target_include_directories(json_parser INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
	json_parser 
	INTERFACE
	iparser
	idata
	string
	array
	object
)

add_library(json_serializer INTERFACE)
target_sources(json_serializer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/json_serializer.cpp)
target_include_directories(json_serializer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
	json_serializer 
	INTERFACE
	iserializer 
	idata
	composite
	value
	string
	array
	object
)
add_library(json_serializer_test STATIC)
target_link_libraries(json_serializer_test PRIVATE json_serializer)
	
add_library(json_common INTERFACE)
target_include_directories(json_common INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# add_subdirectory(tests EXCLUDE_FROM_ALL)