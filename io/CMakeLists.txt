add_library(ireader INTERFACE)
target_include_directories(ireader INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(iwriter INTERFACE)
target_include_directories(iwriter INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(ibytes_reader INTERFACE)
target_include_directories(ibytes_reader INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(ibytes_writer INTERFACE)
target_include_directories(ibytes_writer INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(bytes_reader INTERFACE)
target_sources(bytes_reader INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/bytes_reader.cpp)
target_include_directories(bytes_reader INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(bytes_reader INTERFACE ibytes_reader)