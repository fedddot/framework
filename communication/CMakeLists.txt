add_library(isender INTERFACE)
target_include_directories(isender INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(ireceiver INTERFACE)
target_include_directories(ireceiver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(ireceiver INTERFACE ilistener)

add_library(byte_sender INTERFACE)
target_sources(byte_sender INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/byte_sender.cpp)
target_include_directories(byte_sender INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(byte_sender INTERFACE isender iserializer idata)

add_library(byte_receiver INTERFACE)
target_sources(byte_receiver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/byte_receiver.cpp)
target_include_directories(byte_receiver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(byte_receiver INTERFACE ireceiver iparser idata)

add_library(byte_sender_test STATIC)
target_link_libraries(byte_sender_test PRIVATE byte_sender)