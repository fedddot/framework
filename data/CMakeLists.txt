add_library(idata INTERFACE)
target_sources(idata INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/idata.cpp)
target_include_directories(idata INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(idata_parser INTERFACE)
target_sources(idata_parser INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/idata_parser.cpp)
target_include_directories(idata_parser INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(idata_serializer INTERFACE)
target_sources(idata_serializer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/idata_serializer.cpp)
target_include_directories(idata_serializer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(composite INTERFACE)
target_sources(composite INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/composite.cpp)
target_include_directories(composite INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(object INTERFACE)
target_sources(object INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/object.cpp)
target_include_directories(object INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(array INTERFACE)
target_sources(array INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/array.cpp)
target_include_directories(array INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(string INTERFACE)
target_sources(string INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/string.cpp)
target_include_directories(string INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(data_sender INTERFACE)
target_sources(data_sender INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/data_sender.cpp)
target_include_directories(data_sender INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(data_receiver INTERFACE)
target_sources(data_receiver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/data_receiver.cpp)
target_link_libraries(data_receiver INTERFACE ilistener)
target_include_directories(data_receiver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)