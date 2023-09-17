add_library(ireceiver INTERFACE)
target_include_directories(ireceiver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(ireceiver INTERFACE ilistener)

add_library(package_receiver INTERFACE)
target_sources(package_receiver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/package_receiver.cpp)
target_include_directories(package_receiver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(package_receiver INTERFACE ireceiver ilistener)

# DELETE IT
add_library(package_receiver_test STATIC)
target_link_libraries(package_receiver_test PRIVATE package_receiver)

add_library(isender INTERFACE)
target_include_directories(isender INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(package_sender INTERFACE)
target_sources(package_sender INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/package_sender.cpp)
target_include_directories(package_sender INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(package_sender INTERFACE isender)

# DELETE IT
add_library(package_sender_test STATIC)
target_link_libraries(package_sender_test PRIVATE package_sender)

add_library(icommunication_manager INTERFACE)
target_include_directories(icommunication_manager INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(icommunication_manager INTERFACE ilistener)

add_library(communication_manager INTERFACE)
target_sources(communication_manager INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/communication_manager.cpp)
target_include_directories(communication_manager INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(communication_manager INTERFACE icommunication_manager ilistener)

# DELETE IT
add_library(communication_manager_test STATIC)
target_link_libraries(communication_manager_test PRIVATE communication_manager)