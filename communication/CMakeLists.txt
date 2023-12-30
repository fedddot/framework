# Basic interfaces
add_library(ireceiver INTERFACE)
target_include_directories(ireceiver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(ireceiver INTERFACE ilistener)

add_library(isender INTERFACE)
target_include_directories(isender INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(communication_manager INTERFACE)
target_include_directories(communication_manager INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(communication_manager INTERFACE generics)

# Packaged data handling
add_library(package_descriptor INTERFACE)
target_sources(package_descriptor INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/package_descriptor.cpp)
target_include_directories(package_descriptor INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(package_receiver INTERFACE)
target_sources(package_receiver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/package_receiver.cpp)
target_include_directories(package_receiver INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(package_receiver INTERFACE ilistener dispatcher package_descriptor)

add_library(package_sender INTERFACE)
target_sources(package_sender INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/package_sender.cpp)
target_include_directories(package_sender INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(package_sender INTERFACE isender package_descriptor)

add_library(package_manager INTERFACE)
target_sources(package_manager INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/package_manager.cpp)
target_include_directories(package_manager INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(package_manager INTERFACE isender package_descriptor package_receiver package_sender)

add_subdirectory(transport_layer)

add_subdirectory(tests EXCLUDE_FROM_ALL)