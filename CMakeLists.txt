#cmake -G "MinGW Makefiles"
message(STATUS "${CMAKE_CURRENT_LIST_FILE}")
cmake_minimum_required(VERSION 2.8.12)
Project(QOds)

set(LIBRARY_OUTPUT_PATH "${QOds_BINARY_DIR}/lib")

set(CMAKE_CXX_STANDARD 17)

message(STATUS ${CMAKE_SYSTEM}) # print OS name

#set (BUILD_STATIC_LIBRARIES "1")
if (BUILD_STATIC_LIBRARIES)
    set(ODS_STATIC "1")
    set(QUAZIP_STATIC "1")
    set(ZLIB_STATIC "1")
endif (BUILD_STATIC_LIBRARIES)

if(NOT TARGET zlib)
    add_subdirectory(zlib)
endif()
add_subdirectory(quazip)
add_subdirectory(ods)
add_subdirectory(app)
